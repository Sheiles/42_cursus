#!/bin/sh
set -eu

read_secret() {
    if [ ! -r "$1" ]; then
        echo "Required secret is not readable: $1" >&2
        exit 1
    fi
    tr -d '\r\n' < "$1"
}

sql_escape() {
    printf '%s' "$1" | sed "s/\\\\/\\\\\\\\/g; s/'/''/g"
}

root_password=$(read_secret /run/secrets/db_root_password)
db_password=$(read_secret /run/secrets/db_password)

if [ -z "$root_password" ] || [ -z "$db_password" ]; then
    echo "Database passwords must not be empty." >&2
    exit 1
fi
if [ -z "${MYSQL_DATABASE:-}" ] || [ -z "${MYSQL_USER:-}" ]; then
    echo "MYSQL_DATABASE and MYSQL_USER must be set." >&2
    exit 1
fi
case "$MYSQL_DATABASE$MYSQL_USER" in
    *[!A-Za-z0-9_]*)
        echo "Database and user names may contain only letters, digits and _." >&2
        exit 1
        ;;
esac

mkdir -p /run/mysqld /var/lib/mysql
chown -R mysql:mysql /run/mysqld /var/lib/mysql

if [ ! -d /var/lib/mysql/mysql ]; then
    mariadb-install-db \
        --user=mysql \
        --datadir=/var/lib/mysql \
        --auth-root-authentication-method=normal \
        --skip-test-db
fi

esc_db_password=$(sql_escape "$db_password")
esc_root_password=$(sql_escape "$root_password")

umask 077
{
    printf "CREATE DATABASE IF NOT EXISTS \`%s\`;\n" "$MYSQL_DATABASE"
    printf "CREATE USER IF NOT EXISTS '%s'@'%%' IDENTIFIED BY '%s';\n" "$MYSQL_USER" "$esc_db_password"
    printf "ALTER USER '%s'@'%%' IDENTIFIED BY '%s';\n" "$MYSQL_USER" "$esc_db_password"
    printf "GRANT ALL PRIVILEGES ON \`%s\`.* TO '%s'@'%%';\n" "$MYSQL_DATABASE" "$MYSQL_USER"
    printf "ALTER USER 'root'@'localhost' IDENTIFIED BY '%s';\n" "$esc_root_password"
    printf "FLUSH PRIVILEGES;\n"
} > /run/mariadb-init.sql
chown mysql:mysql /run/mariadb-init.sql
chmod 600 /run/mariadb-init.sql

exec mariadbd --user=mysql --console --init-file=/run/mariadb-init.sql
