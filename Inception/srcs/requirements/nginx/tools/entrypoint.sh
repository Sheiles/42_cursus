#!/bin/sh
set -eu

if [ -z "${DOMAIN_NAME:-}" ]; then
    echo "DOMAIN_NAME must be set." >&2
    exit 1
fi

envsubst '${DOMAIN_NAME}' \
    < /etc/nginx/templates/default.conf.template \
    > /etc/nginx/conf.d/default.conf

openssl req -x509 -nodes -days 365 \
    -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/private.key \
    -out /etc/nginx/ssl/certificate.crt \
    -subj "/CN=$DOMAIN_NAME" \
    -addext "subjectAltName=DNS:$DOMAIN_NAME"
chmod 600 /etc/nginx/ssl/private.key

exec nginx -g 'daemon off;'
