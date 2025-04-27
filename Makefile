# Define directories
SRC_DIR := src
BIN_DIR := bin

# Define compiler and flags
CXX := g++
CXXFLAGS := -std=c++20 -O3 -Wall
CXXDEBUG := -std=c++20 -g  -Wall

# Find all .cpp files in the src directory
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
# Generate binary file names by replacing src/ with bin/ and removing .cpp
BINARIES := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%,$(SRC_FILES))

# Define golang compiler and flags
GO := go

# Find all .go files in the src directory
GO_SRC_FILES := $(wildcard $(SRC_DIR)/*.go)
# Generate binary file names by replacing src/ with bin/ and removing .cpp
GO_BINARIES := $(patsubst $(SRC_DIR)/%.go,$(BIN_DIR)/%,$(GO_SRC_FILES))

# Default target
all: $(BINARIES) $(GO_BINARIES)

# Rule to create binaries from source files
$(BIN_DIR)/%: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	@echo -n "\033[1;36mCompiling $< to $@... \033[0m"
	@$(CXX) $(CXXFLAGS) -o $@ $<
	@echo "\033[1;32mCompiled Successfully\033[0m"

# Rule to create GO binaries from source files
$(BIN_DIR)/%: $(SRC_DIR)/%.go
	@mkdir -p $(BIN_DIR)
	@echo -n "\033[1;36mCompiling $< to $@... \033[0m"
	@$(GO) build -o $@ $<
	@echo "\033[1;32mCompiled Successfully\033[0m"

# Rule to build a specific binary
build:
	@if [ -z "$(FILE)" ]; then \
		$(MAKE) all; \
	else \
		$(MAKE) $(BIN_DIR)/$(basename $(notdir $(FILE))); \
	fi

# Run all tests
test:
	@echo "\033[1;33mRunning tests for all files in $(SRC_DIR)\033[0m"
	@python3 ./run_tests.py

# Clean up build artifacts
clean:
	@rm -rf $(BIN_DIR)/*
	@echo "\033[1;33mAll build artifacts removed from $(BIN_DIR)\033[0m"

# Format all files
fmt:
	@clang-format -i src/*cpp
	@echo "\033[1;33mFormatted all CPP files in $(SRC_DIR)\033[0m"
	@go fmt src/*go
	@echo "\033[1;33mFormatted all Go files in $(SRC_DIR)\033[0m"
	@python3 -m ruff format src/*py
	@echo "\033[1;33mFormatted all Python files in $(SRC_DIR)\033[0m"

.PHONY: all build clean fmt test
