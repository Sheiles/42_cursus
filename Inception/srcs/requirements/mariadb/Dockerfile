curl -kI https://sheiles.42.fr/FROM debian:12-slim

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends mariadb-server \
    && rm -rf /var/lib/apt/lists/* \
    && rm -rf /var/lib/mysql/* \
    && mkdir -p /run/mysqld \
    && chown -R mysql:mysql /run/mysqld /var/lib/mysql

COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
COPY tools/entrypoint.sh /usr/local/bin/mariadb-entrypoint

RUN chmod 755 /usr/local/bin/mariadb-entrypoint

EXPOSE 3306

ENTRYPOINT ["/usr/local/bin/mariadb-entrypoint"]
