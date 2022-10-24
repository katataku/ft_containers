NAME = cocntainers
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -MMD -MP
SRCS = $(wildcard srcs/*/*.cpp) containers.cpp
OBJS = $(SRCS:%.cpp=%.o)
DEPS = $(OBJS:%.o=%.d)
HEADERS = $(wildcard srcs/*/*.hpp)
INCS = $(addprefix -I,$(wildcard srcs/*)) 

ifdef DEBUG
	CXXFLAGS += -D DEBUG=true -g -fsanitize=address
endif

# -------------------------- Rules For Build ------------------------------

$(NAME): $(OBJS) ## Build
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

$(NAME_BONUS): $(OBJS) ## Build
	$(CXX) $(CXXFLAGS) -o $(NAME_BONUS) $(OBJS)

bonus: $(NAME_BONUS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCS) -o $@ -c $<

all: $(NAME) ## Build

fclean: clean ## Delete executable
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

clean: ## Delete object files
	$(RM) $(OBJS) $(DEPS)

re: fclean all ## Rebuild

debug: fclean ## Build in debug mode
	make DEBUG=true

.PHONY: all fclean clean re bonus

-include $(DEPS)

# -------------------------- Rules For Test -------------------------------

.PHONY: utest
utest: ## Exec unit tests1
	make -C tests/unit_test

.PHONY: itest
itest: ## Exec unit tests1
	make itest-ok && make itest-error

INTEGRATION_TEST_SHELL_OK = ./tests/integration_test/ok.sh
.PHONY: itest-ok
itest-ok: ## Exec unit tests1
	@if [ ! -x $(INTEGRATION_TEST_SHELL_OK) ]; then\
		chmod +x $(INTEGRATION_TEST_SHELL_OK);\
	fi
	$(INTEGRATION_TEST_SHELL_OK)


INTEGRATION_TEST_SHELL_ERROR = ./tests/integration_test/error.sh
.PHONY: itest-error
itest-error: ## Exec unit tests
	@if [ ! -x $(INTEGRATION_TEST_SHELL_ERROR) ]; then\
		chmod +x $(INTEGRATION_TEST_SHELL_ERROR);\
	fi
	$(INTEGRATION_TEST_SHELL_ERROR)

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

PHONY: dc-bench
dc-bench:
	docker exec -it $(CONTAINER) /bin/bash -c \
	"cd tests/bench &&\
	g++ mybenchmark.cc -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark &&\
	 ./mybenchmark --benchmark_repetitions=1"
# ---------------------------- Rules For Help -----------------------------

.PHONY: help
help: ## Display this help screen
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' Makefile | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: h
h: help ## shorthand 'help' command
