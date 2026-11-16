#!/bin/sh
set -eu

read_secret() {
    if [ ! -r "$1" ]; then
        echo "Required secret is not readable: $1" >&2
        exit 1
    fi
    cat "$1"
}

root_password=$(read_secret /run/secrets/db_root_password)
db_password=$(read_secret /run/secrets/db_password)

if [ -z "$root_password" ] || [ -z "$db_password" ]; then
    echo "Database passwords must not be empty." >&2
    exit 1
fi
case "$root_password$db_password" in
    *[!A-Za-z0-9_-]*)
        echo "Database passwords must contain only letters, digits, _ or -." >&2
        exit 1
        ;;
esac
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

chown -R mysql:mysql /var/lib/mysql

if [ ! -d /var/lib/mysql/mysql ]; then
    mariadb-install-db \
        --user=mysql \
        --datadir=/var/lib/mysql \
        --auth-root-authentication-method=normal \
        --skip-test-db
fi

umask 077
cat > /run/mariadb-init.sql <<SQL
CREATE DATABASE IF NOT EXISTS \`$MYSQL_DATABASE\`;
CREATE USER IF NOT EXISTS '$MYSQL_USER'@'%' IDENTIFIED BY '$db_password';
ALTER USER '$MYSQL_USER'@'%' IDENTIFIED BY '$db_password';
GRANT ALL PRIVILEGES ON \`$MYSQL_DATABASE\`.* TO '$MYSQL_USER'@'%';
ALTER USER 'root'@'localhost' IDENTIFIED BY '$root_password';
FLUSH PRIVILEGES;
SQL
chown mysql:mysql /run/mariadb-init.sql
chmod 600 /run/mariadb-init.sql

exec mariadbd --user=mysql --console --init-file=/run/mariadb-init.sql
