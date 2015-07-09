# Makefile that builds within a complex project structure.

# Project build constants, via simple expansion ":=" at declaration time.
CXX				:= g++
CSTD 			:= -std=c++14
CXXFLAGS	:= -g -Wall -pthread
EXEC 			:= test_project
LIB 			:= -L lib
INC 			:= -I include

# Variables holding file paths, via simple expansion ":=" at declaration time.
SRC_DIR		:= src
BUILD_DIR	:= build
TARGET 		:= bin/$(EXEC).exe

# Source and object file creation.
SOURCES 	:= $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS 	:= $(patsubst $(SRC_DIR)/%, $(BUILD_DIR)/%, $(SOURCES:.cpp=.o))

# This prints to the standard output for formatting.
$(info )

# Default target.
all: $(EXEC)

# Intermidiate target.
$(EXEC): $(TARGET)

# Main target - linking objects.
$(TARGET): $(OBJECTS)
	@echo -e "\n  Linking...\n"
	$(CXX) $(CSTD) $(CXXFLAGS) $(LIB) $^ -o $@
	@echo -e "\n  Successfully built" $(EXEC)

# Object target - compiling source (first calls "build" target).
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CSTD) $(CXXFLAGS) $(INC) -c $< -o $@

# To remove generated files.
clean:
	@echo -e "  Cleaning...\n"; 
	rm -rf -R $(BUILD_DIR) $(TARGET)

# Cleaning the test structure.
clean-tests:
	$(MAKE) -C test clean

# Building the testing framework and associated tests.
tests:
	$(MAKE) -C test

# Run's the executable.
run:
	@./bin/$(EXEC)

# Necessary to explicitly tell make that "clean" isn't associated with a file.
.PHONY: all tests clean run
