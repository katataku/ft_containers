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

TEST_SRCS = tests/unit_test/main.cpp
FT_MAIN.O = tests/unit_test/ft_main.o
STD_MAIN.O = tests/unit_test/std_main.o
TEST_OBJS = $(FT_MAIN.O) $(STD_MAIN.O)
TEST_DEPS = $(TEST_OBJS:%.o=%.d)
FT_CONTAINER = tests/unit_test/ft_container
STD_CONTAINER = tests/unit_test/std_container
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
	$(RM) $(OBJS) $(DEPS) $(TEST_OBJS) $(TEST_DEPS) $(FT_CONTAINER_OUTPUT) $(STD_CONTAINER_OUTPUT)

re: fclean all ## Rebuild

.PHONY: all fclean clean re bonus

-include $(TEST_DEPS)

# -------------------------- Rules For Test -------------------------------
$(FT_MAIN.O): $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) $(INCS) -o $@ -c $< -DLIB=ft
$(STD_MAIN.O): $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) $(INCS) -o $@ -c $< -DLIB=std

$(FT_CONTAINER): $(FT_MAIN.O) 
	$(CXX) $(CXXFLAGS) -o $@ $(FT_MAIN.O)

$(STD_CONTAINER): $(STD_MAIN.O) 
	$(CXX) $(CXXFLAGS) -o $@ $(STD_MAIN.O)

.PHONY: test
test: $(FT_CONTAINER) $(STD_CONTAINER)## Exec unit tests1
	$(STD_CONTAINER) | tee $(STD_CONTAINER_OUTPUT)
	$(FT_CONTAINER)| tee $(FT_CONTAINER_OUTPUT)
	diff $(STD_CONTAINER).out $(FT_CONTAINER).out

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
