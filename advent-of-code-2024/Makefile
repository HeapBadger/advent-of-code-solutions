# Compiler and Tools
CC = gcc
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = test
OBJ_DIR = obj
BIN_DIR = bin
CFLAGS = -Wall -Wextra -pedantic -std=c99 -I$(INCLUDE_DIR)
LDFLAGS = -lcunit
FORMAT = clang-format-15
TIDY = clang-tidy $(addprefix --extra-arg=,$(subst -I,-I ,$(CFLAGS)))

# Source files and objects
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $(TEST_FILES:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

# Target executables
EXEC = adventofcode
TEST_EXEC = test_adventofcode

# Create necessary directories
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Default target: build the main executable
all: $(BIN_DIR)/$(EXEC)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test files into object files
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test_main.c into an object file (for the test executable)
$(OBJ_DIR)/test_main.o: $(TEST_DIR)/test_main.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

# Link object files into the main executable
$(BIN_DIR)/$(EXEC): $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
	$(CC) $^ -o $@ $(LDFLAGS)

# Link object files into the test executable (exclude main.o from the test build)
$(BIN_DIR)/$(TEST_EXEC): $(OBJ_FILES) $(OBJ_DIR)/test_main.o
	$(CC) $(filter-out $(OBJ_DIR)/main.o, $^) -o $@ $(LDFLAGS)

# Static analysis with clang-tidy
tidy:
	$(TIDY) $(SRC_FILES) $(TEST_FILES)

# Format code using clang-format
format:
	$(FORMAT) -i $(SRC_DIR)/*.c $(INCLUDE_DIR)/*.h $(TEST_DIR)/*.c

# Run tests (compile and execute the test runner)
test: all $(BIN_DIR)/$(TEST_EXEC)
	./$(BIN_DIR)/$(TEST_EXEC)

# Run tests with Valgrind
valgrind: $(BIN_DIR)/$(TEST_EXEC)
	valgrind --leak-check=full ./$(BIN_DIR)/$(TEST_EXEC)

# Run the adventofcode program (either all challenges or a specific day)
run: $(BIN_DIR)/$(EXEC)
	@./$(BIN_DIR)/$(EXEC) $(ARGS)

# Clean up any specified arguments and pass them to the binary
ARGS = $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all tidy format test clean valgrind run
