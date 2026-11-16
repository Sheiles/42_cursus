*This project has been created as part of the 42 curriculum by sheiles.*

# Inception

## Description

Inception is a small system-administration project that builds a WordPress
website inside a Docker Compose infrastructure. It runs three purpose-built
containers: NGINX provides the HTTPS entry point, WordPress runs PHP-FPM, and
MariaDB stores the site database. A private Docker bridge network connects the
services. Named volumes persist the database and website files under
`/home/sheiles/data` on the host.

The images are built from the Debian 12 slim base image; no ready-made service
images are used. Configuration and service build files are in `srcs/`, while
local-only credentials are stored in the ignored `secrets/` directory.

### Design choices

- **Virtual machines vs Docker:** a virtual machine runs a complete guest
  operating system and its own kernel; Docker containers isolate processes
  while sharing the host kernel. Containers are lighter and start faster, but
  provide a different isolation boundary.
- **Secrets vs environment variables:** environment variables are convenient
  for non-sensitive configuration, but can be exposed through process or
  container inspection. Docker secrets are mounted as files and are used here
  for passwords. The `.env` file contains only non-secret settings.
- **Docker network vs host network:** the private bridge network gives the
  services name-based connectivity without exposing their internal ports.
  Host networking would share the host network namespace and bypass that
  isolation.
- **Docker volumes vs bind mounts:** Docker-managed volumes are portable and
  persist independently of container lifecycles. Bind mounts map an arbitrary
  host path directly into a container. This project uses named volumes with
  the local volume driver configured to store their data in the required host
  directories.

## Instructions

Run this project on a Linux virtual machine with Docker Engine, the Docker
Compose plugin, and GNU Make installed. Ensure the VM can resolve
`sheiles.42.fr` to its own IP address (for local testing, add the mapping to
the VM's `/etc/hosts` and to the client machine's hosts file).

Create four local secret files before starting:

```sh
mkdir -p secrets
umask 077
openssl rand -hex 32 > secrets/db_root_password.txt
openssl rand -hex 32 > secrets/db_password.txt
openssl rand -hex 32 > secrets/wp_owner_password.txt
openssl rand -hex 32 > secrets/wp_editor_password.txt
```

Keep the generated values private; these files are excluded from Git. Then
build and start the project with `make`. Visit
`https://sheiles.42.fr/` for the site or `https://sheiles.42.fr/wp-admin/` for
the administration panel. The generated TLS certificate is self-signed, so a
browser warning is expected in a local setup.

See [USER_DOC.md](./USER_DOC.md) for operating instructions and
[DEV_DOC.md](./DEV_DOC.md) for setup and maintenance details.

## Resources

- [Docker Compose documentation](https://docs.docker.com/compose/)
- [Docker volumes](https://docs.docker.com/engine/storage/volumes/)
- [Docker secrets](https://docs.docker.com/compose/how-tos/use-secrets/)
- [NGINX documentation](https://nginx.org/en/docs/)
- [WordPress developer resources](https://developer.wordpress.org/)
- [MariaDB documentation](https://mariadb.com/kb/en/documentation/)

AI assistance was used to scaffold the Docker Compose and service configuration,
and to draft the project, user, and developer documentation from the Inception
requirements. The resulting configuration should be reviewed and run on the
required Linux virtual machine before evaluation.
