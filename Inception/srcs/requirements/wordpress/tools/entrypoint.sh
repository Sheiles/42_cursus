#!/bin/sh
set -eu

read_secret() {
    if [ ! -r "$1" ]; then
        echo "Required secret is not readable: $1" >&2
        exit 1
    fi
    cat "$1"
}

db_password=$(read_secret /run/secrets/db_password)
owner_password=$(read_secret /run/secrets/wp_owner_password)
editor_password=$(read_secret /run/secrets/wp_editor_password)

if [ -z "$db_password" ] || [ -z "$owner_password" ] || [ -z "$editor_password" ]; then
    echo "Passwords must not be empty." >&2
    exit 1
fi
case "$db_password$owner_password$editor_password" in
    *[!A-Za-z0-9_-]*)
        echo "Passwords must contain only letters, digits, _ or -." >&2
        exit 1
        ;;
esac

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

cd /var/www/html
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

wp --allow-root core is-installed --path=/var/www/html >/dev/null 2>&1 || \
    wp --allow-root core install \
        --path=/var/www/html \
        --url="https://$DOMAIN_NAME" \
        --title="$WP_TITLE" \
        --admin_user="$WP_ADMIN_USER" \
        --admin_password="$owner_password" \
        --admin_email="$WP_ADMIN_EMAIL" \
        --skip-email

if ! wp --allow-root user get "$WP_AUTHOR_USER" --field=ID --path=/var/www/html >/dev/null 2>&1; then
    wp --allow-root user create "$WP_AUTHOR_USER" "$WP_AUTHOR_EMAIL" \
        --role=author \
        --user_pass="$editor_password" \
        --path=/var/www/html
fi

chown -R www-data:www-data /var/www/html
exec php-fpm8.2 --nodaemonize
