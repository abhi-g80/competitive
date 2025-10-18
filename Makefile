# Initialize environment
init: check-ruff create-include-dir

# Create standard headers
create-include-dir:
	@mkdir -p $(INCLUDE_DIR)
	@if [ ! -f "$(INCLUDE_DIR)/stdint_wrapper.h" ]; then \
		echo "\033[1;33mCreating standard headers...\033[0m"; \
		echo "#pragma once" > $(INCLUDE_DIR)/stdint_wrapper.h; \
		echo "#include <cstdint>" >> $(INCLUDE_DIR)/stdint_wrapper.h; \
		echo "#include <cstddef>" >> $(INCLUDE_DIR)/stdint_wrapper.h; \
		echo "#include <cstdlib>" >> $(INCLUDE_DIR)/stdint_wrapper.h; \
		echo "// Add more standard includes as needed" >> $(INCLUDE_DIR)/stdint_wrapper.h; \
		echo "\033[1;32mCreated standard headers\033[0m"; \
	fi
SRC_DIR := src
BIN_DIR := bin
TEST_DIR := test
INCLUDE_DIR := $(SRC_DIR)/include

# Create include directory if it doesn't exist
$(shell mkdir -p $(INCLUDE_DIR))

# Define compilers and flags
CXX := g++
CXXFLAGS := -std=c++20 -O3 -Wall -Wextra
CXXDEBUG := -std=c++20 -g -Wall -Wextra
CXXINCLUDES := -I$(SRC_DIR)/include

GO := go
GOFLAGS :=

# Find all source files by language
CPP_SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
CPP_SRC_FILES_N := $(wildcard $(SRC_DIR)/neetcode*.cpp)
GO_SRC_FILES := $(wildcard $(SRC_DIR)/*.go)
PY_SRC_FILES := $(wildcard $(SRC_DIR)/*.py)

# Generate binary file names
CPP_BINARIES := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%,$(CPP_SRC_FILES))
CPP_BINARIES_N := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%,$(CPP_SRC_FILES_N))
GO_BINARIES := $(patsubst $(SRC_DIR)/%.go,$(BIN_DIR)/%,$(GO_SRC_FILES))

# Default target
default: all
all: init cpp go

# Language-specific targets
cpp: $(CPP_BINARIES)
go: $(GO_BINARIES)

# Rule to create C++ binaries from source files
$(BIN_DIR)/%: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	@printf "\033[1;36mCompiling C++ $< to $@... \033[0m"
	@$(CXX) $(CXXFLAGS) $(CXXINCLUDES) -o $@ $< || { echo "\033[1;31mFailed\033[0m"; exit 1; }
	@echo "\033[1;32mDone\033[0m"

# Rule to create Go binaries from source files
$(BIN_DIR)/%: $(SRC_DIR)/%.go
	@mkdir -p $(BIN_DIR)
	@printf "\033[1;36mCompiling Go $< to $@... \033[0m"
	@$(GO) build $(GOFLAGS) -o $@ $<
	@echo "\033[1;32mDone\033[0m"

# Rule to build a specific binary
build:
	@if [ -z "$(FILE)" ]; then \
		$(MAKE) all; \
	elif [ -f "$(SRC_DIR)/$(FILE).cpp" ]; then \
		$(MAKE) $(BIN_DIR)/$(FILE); \
	elif [ -f "$(SRC_DIR)/$(FILE).go" ]; then \
		$(MAKE) $(BIN_DIR)/$(FILE); \
	else \
		echo "\033[1;31mError: File $(SRC_DIR)/$(FILE).* not found\033[0m"; \
		exit 1; \
	fi

# Run tests for each language
test: test-cpp test-go test-py

# Run tests for C++ binaries
test-cpp:
	@echo "\033[1;33mRunning tests for C++ binaries:\033[0m"
	@for bin in $(CPP_BINARIES); do \
		echo "\033[1;34mTesting $${bin}...\033[0m"; \
		$${bin} || echo "\033[1;31mTest failed: $${bin}\033[0m"; \
	done

# Run tests for Neetcode C++ binaries
test-neetcode-cpp: cpp
	@echo "\033[1;33mRunning tests for Neetcode C++ binaries:\033[0m"
	@for bin in $(CPP_BINARIES_N); do \
		echo "\033[1;34mTesting $${bin}...\033[0m"; \
		$${bin} || echo "\033[1;31mTest failed: $${bin}\033[0m"; \
	done

# Run tests for Go packages
test-go:
	@echo "\033[1;33mRunning tests for Go packages:\033[0m"
	@cd $(SRC_DIR) && $(GO) test ./... || echo "\033[1;31mGo tests failed\033[0m"

# Run tests for Python files
test-py: check-ruff
	@if [ -n "$(PY_SRC_FILES)" ]; then \
		echo "\033[1;33mRunning tests for Python files:\033[0m"; \
		python3 ./run_tests.py; \
	else \
		echo "\033[1;33mNo Python files to test\033[0m"; \
	fi

# Debug build for C++ files
debug: CXXFLAGS = $(CXXDEBUG)
debug: cpp

# Clean up build artifacts
clean:
	@rm -rf $(BIN_DIR)/*
	@echo "\033[1;33mAll build artifacts removed from $(BIN_DIR)\033[0m"

# Format all files
fmt: fmt-cpp fmt-go fmt-py

fmt-cpp:
	@if [ -n "$(CPP_SRC_FILES)" ]; then \
		echo "\033[1;33mFormatting C++ files...\033[0m"; \
		clang-format -i $(CPP_SRC_FILES); \
	else \
		echo "\033[1;33mNo C++ files to format\033[0m"; \
	fi

fmt-go:
	@if [ -n "$(GO_SRC_FILES)" ]; then \
		echo "\033[1;33mFormatting Go files...\033[0m"; \
		$(GO) fmt $(GO_SRC_FILES); \
	else \
		echo "\033[1;33mNo Go files to format\033[0m"; \
	fi

check-ruff:
	@python3 -c "import ruff" > /dev/null 2>&1 || (echo "\033[1;33mRuff not found. Installing...\033[0m" && pip install ruff)

fmt-py: check-ruff
	@if [ -n "$(PY_SRC_FILES)" ]; then \
		echo "\033[1;33mFormatting Python files...\033[0m"; \
		python3 -m ruff format $(PY_SRC_FILES); \
	else \
		echo "\033[1;33mNo Python files to format\033[0m"; \
	fi

# Help target
help:
	@echo "Available targets:"
	@echo "  all       - Build all C++ and Go binaries (default)"
	@echo "  cpp       - Build only C++ binaries"
	@echo "  go        - Build only Go binaries"
	@echo "  debug     - Build C++ binaries with debug flags"
	@echo "  build     - Build a specific file (use FILE=filename without extension)"
	@echo "  test      - Run all tests"
	@echo "  test-cpp  - Run tests for C++ binaries"
	@echo "  test-go   - Run Go tests"
	@echo "  test-py   - Run Python tests"
	@echo "  fmt       - Format all source files"
	@echo "  clean     - Remove all build artifacts"
	@echo "  init      - Initialize environment (create includes, install tools)"
	@echo "  help      - Display this help message"

.PHONY: all cpp go build test test-cpp test-go test-py check-ruff create-include-dir init debug clean fmt fmt-cpp fmt-go fmt-py help
