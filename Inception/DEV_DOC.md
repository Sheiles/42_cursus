# Developer documentation

## Prerequisites and initial setup

Use a Linux virtual machine with Docker Engine, the Docker Compose plugin,
GNU Make, and OpenSSL. Clone or copy this project to the VM and ensure
`sheiles.42.fr` resolves to the VM's local IP address. For a local-only setup,
add the mapping to `/etc/hosts` on the VM and on the client used to browse the
site.

The non-sensitive settings are in `srcs/.env`. They define the learner login,
domain, database name/user, and WordPress account names. To use another login,
update `LOGIN` and `DOMAIN_NAME` there and adjust the documented host data
path and domain accordingly.

Create the four secret files expected by Compose:

```sh
mkdir -p secrets
umask 077
openssl rand -hex 32 > secrets/db_root_password.txt
openssl rand -hex 32 > secrets/db_password.txt
openssl rand -hex 32 > secrets/wp_owner_password.txt
openssl rand -hex 32 > secrets/wp_editor_password.txt
```

The files must contain non-empty alphanumeric passwords (the supplied command
generates hexadecimal values). They are ignored by Git and must remain private.
The WordPress account passwords are used at initial installation. Updating
their files later does not rotate existing WordPress accounts.

## Build and launch

```sh
make
```

The Makefile creates the host directories under `/home/sheiles/data`, then
builds the NGINX, WordPress/PHP-FPM, and MariaDB images from their own
Dockerfiles and starts the Compose project. Only NGINX publishes a port, 443.
The Compose network is private to the project.

## Container management

```sh
make ps
make logs
make down
make build
```

Equivalent direct commands are:

```sh
docker compose --project-name inception --env-file srcs/.env \
  -f srcs/docker-compose.yml ps
docker compose --project-name inception --env-file srcs/.env \
  -f srcs/docker-compose.yml logs --follow
docker compose --project-name inception --env-file srcs/.env \
  -f srcs/docker-compose.yml down
```

`make down` stops and removes the containers and network but preserves named
volumes and their data. Back up the data directories and secrets before
maintenance. Removing or replacing `/home/sheiles/data/mariadb` or
`/home/sheiles/data/wordpress` can cause permanent data loss.

## Persistence and project layout

- `srcs/docker-compose.yml` defines the services, private network, secrets,
  restart policies, and two named volumes.
- `srcs/requirements/nginx/` contains the HTTPS reverse-proxy configuration
  and Dockerfile.
- `srcs/requirements/wordpress/` contains the PHP-FPM image and WordPress
  initialization script.
- `srcs/requirements/mariadb/` contains the database image, server
  configuration, and initialization script.
- `secrets/` contains local password files and must not be committed.
- The database volume is stored at `/home/sheiles/data/mariadb`; the WordPress
  files volume is stored at `/home/sheiles/data/wordpress`.

Compose volumes use the local driver with bind options to map the named
volumes to those host paths. NGINX mounts WordPress files read-only.
