NAME = containers
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -MMD -MP
SRCS = $(wildcard srcs/*/*.cpp) containers.cpp
OBJS = $(SRCS:%.cpp=%.o)
DEPS = $(OBJS:%.o=%.d)
HEADERS = $(wildcard include/*.hpp)
INCS = -Iinclude
ifdef DEBUG
	CXXFLAGS += -D DEBUG=true -g -fsanitize=address
endif

# -------------------------- Rules For Build ------------------------------

$(NAME): $(OBJS) ## Build
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCS) -o $@ -c $<

all: $(NAME) ## Build

fclean: clean ## Delete executable
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

clean: ## Delete object files
	$(RM) $(OBJS) $(DEPS)

re: fclean all ## Rebuild

.PHONY: all fclean clean re bonus

-include $(DEPS)

# -------------------------- Rules For Test -------------------------------
TEST_SRCS = tests/unit_test/main.cpp
TEST_OBJS = $(TEST_SRCS:%.cpp=%.o)
TEST_DEPS = $(TEST_OBJS:%.o=%.d)
FT_CONTAINER = tests/unit_test/ft_container
STD_CONTAINER = tests/unit_test/std_container

$(FT_CONTAINER): $(TEST_OBJS) 
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJS) -DLIB=FT

$(STD_CONTAINER): $(TEST_OBJS) 
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJS) -DLIB=STD

.PHONY: test
test: $(FT_CONTAINER) $(STD_CONTAINER)## Exec unit tests1
	$(STD_CONTAINER) | tee $(STD_CONTAINER).out
	$(FT_CONTAINER)| tee $(FT_CONTAINER).out
	diff $(STD_CONTAINER).out $(FT_CONTAINER).out


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
	./mybenchmark --benchmark_repetitions=1  > STD.out &&\
	./mybenchmark --benchmark_repetitions=1 > FT.out &&\
	paste FT.out STD.out > join.out  &&\
	sed '1,3d' ./join.out |awk '{print $1,",", $2 / $8}' > result.csv\
	"
# ---------------------------- Rules For Help -----------------------------

.PHONY: help
help: ## Display this help screen
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' Makefile | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: h
h: help ## shorthand 'help' command
