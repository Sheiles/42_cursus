# User documentation

## Services

- **NGINX** serves the website over HTTPS on port 443 and forwards PHP requests
  to WordPress.
- **WordPress** serves the site using PHP-FPM.
- **MariaDB** stores WordPress data.

The database and site files persist in named volumes backed by
`/home/sheiles/data/mariadb` and `/home/sheiles/data/wordpress`.

## Start and stop

From the project directory on the Linux VM, run:

```sh
make
```

To stop the containers without deleting persistent data:

```sh
make down
```

## Access the site

Open `https://sheiles.42.fr/` for the website or
`https://sheiles.42.fr/wp-admin/` for the administration panel. The local
certificate is self-signed, so the browser may ask you to accept it.

The configured administrator account is `site_owner`; the second account is
`site_editor`. Their passwords are in `secrets/wp_owner_password.txt` and
`secrets/wp_editor_password.txt`, respectively. The MariaDB credentials are in
`secrets/db_password.txt` and `secrets/db_root_password.txt`. These files are
local-only and ignored by Git. Protect them and do not share or commit them.
The WordPress account passwords are applied when the site is first installed;
changing those files later does not change existing account passwords.

## Check that the services are running

```sh
make ps
make logs
docker compose --project-name inception --env-file srcs/.env \
  -f srcs/docker-compose.yml ps
```

The NGINX container is the only service publishing a host port. MariaDB and
PHP-FPM are reachable only over the project network.

## Data and credentials

The named volumes keep the database and WordPress files when containers stop
or are recreated. Do not delete the volume directories to troubleshoot a
container: that permanently removes site data. Credentials are maintained in
the local `secrets/` files; replacing a credential for an existing database
also requires coordinating the database and WordPress configuration.
