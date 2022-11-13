NAME = containers
CXX = c++
CXXFLAGS = -Wall -Wextra -std=c++98 -pedantic -MMD -MP -O3
SRCS = $(wildcard srcs/*/*.cpp) tests/subject_test/main.cpp
OBJS = $(SRCS:%.cpp=%.o)
DEPS = $(OBJS:%.o=%.d)
HEADERS = $(wildcard include/*.hpp)
INCS = -Iinclude
#CXXDEBUGFLAGS += -g -fsanitize=address -pg


UNIT_TEST_DIR = tests/unit_test
TEST_SRCS = $(UNIT_TEST_DIR)/main.cpp 
FT_MAIN.O = $(UNIT_TEST_DIR)/ft_main.o
STD_MAIN.O = $(UNIT_TEST_DIR)/std_main.o
TEST_OBJS = $(FT_MAIN.O) $(STD_MAIN.O)
TEST_DEPS = $(TEST_OBJS:%.o=%.d)
FT_CONTAINER = $(UNIT_TEST_DIR)/ft_container
STD_CONTAINER = $(UNIT_TEST_DIR)/std_container
FT_CONTAINER_OUTPUT= $(FT_CONTAINER).out
STD_CONTAINER_OUTPUT= $(STD_CONTAINER).out

# -------------------------- Rules For Build ------------------------------

$(NAME): $(OBJS) ## Build
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCS) -o $@ -c $<

all: $(NAME) ## Build

fclean: clean ## Delete executable
	$(RM) $(NAME) $(FT_CONTAINER) $(STD_CONTAINER)

clean: ## Delete object files
	$(RM) $(OBJS) $(DEPS)
	$(RM) $(TEST_OBJS) $(TEST_DEPS) $(FT_CONTAINER_OUTPUT) $(STD_CONTAINER_OUTPUT)
	$(RM) ./tests/unit_test/ft_container.md

re: fclean all ## Rebuild

.PHONY: all fclean clean re bonus

-include $(TEST_DEPS)

# -------------------------- Rules For Test -------------------------------
$(FT_MAIN.O): $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) $(CXXDEBUGFLAGS) $(INCS) -o $@ -c $< -DLIB=ft
$(STD_MAIN.O): $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) $(CXXDEBUGFLAGS) $(INCS) -o $@ -c $< -DLIB=std

$(FT_CONTAINER): $(FT_MAIN.O) 
	$(CXX) $(CXXFLAGS) $(CXXDEBUGFLAGS) -o $@ $(FT_MAIN.O)

$(STD_CONTAINER): $(STD_MAIN.O) 
	$(CXX) $(CXXFLAGS) $(CXXDEBUGFLAGS) -o $@ $(STD_MAIN.O)

.PHONY: test
test: $(FT_CONTAINER) $(STD_CONTAINER)## Exec unit tests1
	$(STD_CONTAINER) | tee $(STD_CONTAINER_OUTPUT)
	$(FT_CONTAINER)| tee $(FT_CONTAINER_OUTPUT)
	cp ./tests/unit_test/ft_container.out ./tests/unit_test/ft_container.md
	diff $(STD_CONTAINER).out $(FT_CONTAINER).out

.PHONY: test-re
test-re: fclean test## Exec unit tests1

.PHONY: leak
leak: $(FT_CONTAINER)## Exec unit tests1
	$(FT_CONTAINER)| tee $(FT_CONTAINER_OUTPUT)
	cp ./tests/unit_test/ft_container.out ./tests/unit_test/ft_container.md
	leaks -q -atExit -- $(FT_CONTAINER)

.PHONY: leak_std
leak_std: $(STD_CONTAINER)## Exec unit tests1
	leaks -q -atExit -- $(STD_CONTAINER)

.PHONY: bench
bench: $(FT_CONTAINER) $(STD_CONTAINER)## Exec unit tests1
	time $(STD_CONTAINER) > /dev/null
	time $(FT_CONTAINER)  > /dev/null


-include $(DEPS)



VALGRIND_TEST_SHELL = ./tests/valgrind/valgrind.sh
.PHONY: valgrind
valgrind: ## Exec valgrind tests
	@if [ ! -x $(VALGRIND_TEST_SHELL) ]; then\
		chmod +x $(VALGRIND_TEST_SHELL);\
	fi
	$(VALGRIND_TEST_SHELL)

# -------------------- Rules For Static Analyser --------------------------

.PHONY: format
format: ## Lint source files
	clang-format $(HEADERS) $(SRCS) --dry-run -Werror

.PHONY: lint
lint: ## Lint source files
	cpplint --filter=-legal/copyright,-build/include_subdir $(HEADERS) $(SRCS)

.PHONY: tidy
tidy: ## Tidy source files
	clang-tidy $(HEADERS) $(SRCS) -- $(CXXFLAGS) $(INCS)

# ------------------------- Rules For Docker ------------------------------

CONTAINER = containers
DOCKER_COMPOSE_FILE = ./docker/$(CONTAINER)/docker-compose.yml

.PHONY: dc-build
dc-build: ## Build docker container
	docker compose -f $(DOCKER_COMPOSE_FILE) build 

.PHONY: dc-up
dc-up: ## Run docker container
	docker compose -f $(DOCKER_COMPOSE_FILE) up -d

.PHONY: dc-login
dc-login: ## Login docker container
	docker exec -it $(CONTAINER) /bin/bash

.PHONY: dc-down
dc-down: ## Down docker container
	docker compose -f $(DOCKER_COMPOSE_FILE) down --timeout 1

.PHONY: dc-re
dc-re: dc-down dc-build dc-up ## Rebuild docker image and run container

# ---------------------------- Rules For Help -----------------------------

.PHONY: help
help: ## Display this help screen
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' Makefile | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: h
h: help ## shorthand 'help' command
