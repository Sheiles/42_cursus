#!/bin/sh
set -eu

read_secret() {
    if [ ! -r "$1" ]; then
        echo "Required secret is not readable: $1" >&2
        exit 1
    fi
    tr -d '\r\n' < "$1"
}

db_password=$(read_secret /run/secrets/db_password)
owner_password=$(read_secret /run/secrets/wp_owner_password)
editor_password=$(read_secret /run/secrets/wp_editor_password)

if [ -z "$db_password" ] || [ -z "$owner_password" ] || [ -z "$editor_password" ]; then
    echo "Passwords must not be empty." >&2
    exit 1
fi

if [ -z "${DOMAIN_NAME:-}" ] || [ -z "${MYSQL_DATABASE:-}" ] \
    || [ -z "${MYSQL_USER:-}" ] || [ -z "${MYSQL_HOST:-}" ] \
    || [ -z "${WP_TITLE:-}" ] || [ -z "${WP_ADMIN_USER:-}" ] \
    || [ -z "${WP_ADMIN_EMAIL:-}" ] || [ -z "${WP_AUTHOR_USER:-}" ] \
    || [ -z "${WP_AUTHOR_EMAIL:-}" ]; then
    echo "WordPress configuration environment variables must be set." >&2
    exit 1
fi
case "$WP_ADMIN_USER" in
    *[aA][dD][mM][iI][nN]*)
        echo "WP_ADMIN_USER must not contain 'admin'." >&2
        exit 1
        ;;
esac

mkdir -p /run/php /var/www/html
chown -R www-data:www-data /run/php

if [ ! -f /var/www/html/wp-settings.php ]; then
    cp -a /usr/src/wordpress/. /var/www/html/
fi

cd /var/www/html

i=0
until php -r '
    mysqli_report(MYSQLI_REPORT_OFF);
    $m = @new mysqli(getenv("MYSQL_HOST"), getenv("MYSQL_USER"), $argv[1], getenv("MYSQL_DATABASE"));
    exit($m->connect_errno ? 1 : 0);
' "$db_password" >/dev/null 2>&1; do
    i=$((i + 1))
    if [ "$i" -ge 30 ]; then
        echo "Timed out waiting for MariaDB at $MYSQL_HOST." >&2
        exit 1
    fi
    sleep 1
done

if [ ! -f wp-config.php ]; then
    wp --allow-root config create \
        --path=/var/www/html \
        --dbname="$MYSQL_DATABASE" \
        --dbuser="$MYSQL_USER" \
        --dbpass="$db_password" \
        --dbhost="$MYSQL_HOST" \
        --dbprefix=wp_ \
        --skip-check
fi

if ! wp --allow-root core is-installed --path=/var/www/html >/dev/null 2>&1; then
    wp --allow-root core install \
        --path=/var/www/html \
        --url="https://$DOMAIN_NAME" \
        --title="$WP_TITLE" \
        --admin_user="$WP_ADMIN_USER" \
        --admin_password="$owner_password" \
        --admin_email="$WP_ADMIN_EMAIL" \
        --skip-email
fi

if ! wp --allow-root user get "$WP_AUTHOR_USER" --field=ID --path=/var/www/html >/dev/null 2>&1; then
    wp --allow-root user create "$WP_AUTHOR_USER" "$WP_AUTHOR_EMAIL" \
        --role=author \
        --user_pass="$editor_password" \
        --path=/var/www/html
fi

chown -R www-data:www-data /var/www/html
chmod 640 /var/www/html/wp-config.php
exec php-fpm8.2 --nodaemonize
