include srcs/.env

COMPOSE = docker compose --project-name inception --env-file srcs/.env -f srcs/docker-compose.yml
DATA_DIR = /home/$(LOGIN)/data
SECRETS = secrets/db_root_password.txt \
          secrets/db_password.txt \
          secrets/wp_owner_password.txt \
          secrets/wp_editor_password.txt

.PHONY: all up down build ps logs clean fclean re secrets check-secrets

all: up

check-secrets:
	@for f in $(SECRETS); do \
		if [ ! -s "$$f" ]; then \
			echo "Error: missing or empty secret file: $$f"; \
			echo "Create the secret files first (see README.md), or run: make secrets"; \
			exit 1; \
		fi; \
	done

secrets:
	@mkdir -p secrets
	@umask 077; for f in $(SECRETS); do \
		if [ ! -s "$$f" ]; then \
			openssl rand -hex 32 > "$$f"; \
			echo "Generated $$f"; \
		fi; \
	done

up: check-secrets
	mkdir -p "$(DATA_DIR)/mariadb" "$(DATA_DIR)/wordpress"
	$(COMPOSE) up --build -d

build:
	$(COMPOSE) build

down:
	$(COMPOSE) down

clean:
	$(COMPOSE) down --volumes --rmi local

fclean: clean
	rm -rf "$(DATA_DIR)/mariadb" "$(DATA_DIR)/wordpress"

re: down up

ps:
	$(COMPOSE) ps

logs:
	$(COMPOSE) logs --follow
