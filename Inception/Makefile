include srcs/.env

COMPOSE = docker compose --project-name inception --env-file srcs/.env -f srcs/docker-compose.yml
DATA_DIR = /home/$(LOGIN)/data

.PHONY: all up down build ps logs

all: up

up:
	mkdir -p "$(DATA_DIR)/mariadb" "$(DATA_DIR)/wordpress"
	$(COMPOSE) up --build -d

build:
	$(COMPOSE) build

down:
	$(COMPOSE) down

ps:
	$(COMPOSE) ps

logs:
	$(COMPOSE) logs --follow
