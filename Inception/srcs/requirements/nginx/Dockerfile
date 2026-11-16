FROM debian:12-slim

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        nginx openssl gettext-base \
    && rm -rf /var/lib/apt/lists/* \
    && rm -f /etc/nginx/sites-enabled/default

COPY conf/default.conf.template /etc/nginx/templates/default.conf.template
COPY tools/entrypoint.sh /usr/local/bin/nginx-entrypoint

RUN chmod 755 /usr/local/bin/nginx-entrypoint \
    && mkdir -p /etc/nginx/ssl

EXPOSE 443

ENTRYPOINT ["/usr/local/bin/nginx-entrypoint"]
