FROM debian:12-slim

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        ca-certificates curl php-cli php-fpm php-mysql php-curl php-gd php-intl \
        php-mbstring php-xml php-zip \
    && rm -rf /var/lib/apt/lists/*

RUN curl -fsSL https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
        -o /usr/local/bin/wp \
    && chmod 755 /usr/local/bin/wp \
    && mkdir -p /usr/src/wordpress /var/www/html /run/php \
    && php -d memory_limit=512M /usr/local/bin/wp --allow-root core download --path=/usr/src/wordpress --locale=en_US \
    && chown -R www-data:www-data /var/www/html /run/php \
    && sed -i 's|^error_log = .*|error_log = /proc/self/fd/2|' /etc/php/8.2/fpm/php-fpm.conf

COPY conf/www.conf /etc/php/8.2/fpm/pool.d/www.conf
COPY tools/entrypoint.sh /usr/local/bin/wordpress-entrypoint

RUN chmod 755 /usr/local/bin/wordpress-entrypoint

EXPOSE 9000

ENTRYPOINT ["/usr/local/bin/wordpress-entrypoint"]
