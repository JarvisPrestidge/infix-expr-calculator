# Makefile that builds tests and recompiles the gtest framework if required.

# Variables holding file paths, via simple expansion ":=" at declaration time.
ROOT_DIR	:= ..
GTEST_DIR := gtest-1.7.0
SRC_DIR 	:= $(ROOT_DIR)/src
BUILD_DIR := $(ROOT_DIR)/build

# Project build constants, via simple expansion ":=" at declaration time.
CXX				:= g++
AR 				:= ar
CSTD 			:= -std=c++14
CXXFLAGS	:= -g -Wextra -pthread
CPPFLAGS  := -isystem $(GTEST_DIR)/include
ARFLAGS		:= -rvs

# Variables holding the various lists of objects, sources and exes.
TEST_SRC    := $(wildcard *.cpp) 							# i.e. example_unittest.cpp
PROD_SRC		:= $(TEST_SRC:_unittest.cpp=.cpp) # i.e. example.cpp
TEST_OBJ		:= $(TEST_SRC:.cpp=.o)						# i.e. example_unittest.o
PROD_OBJ		:= $(PROD_SRC:.cpp=.o)						# i.e. example.o
TARGETS			:= $(TEST_SRC:.cpp=.exe)					# i.e. example_unittest.exe

# GoogleTest headers.
GTEST_HEADERS := $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h

# GoogleTest sources.
GTEST_SRCS_   := $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# This prints to the standard output for formatting.
$(info )

# Default target.
all: buildtests

# Intermidate target.
buildtests: $(TARGETS)
	@echo -e "\n  Executing...\n"
	$(TARGETS)

# Main target - linking stage. (gtest_main.a, src.o & src_unittest.o)
$(TARGETS): %_unittest.exe: $(BUILD_DIR)/%.o %_unittest.o gtest_main.a
	@echo -e "\n  Linking...\n"
	$(CXX) $(CSTD) $(CPPFLAGS) $(CXXFLAGS) -Wall -lpthread $^ -o $(basename $@)
	@echo -e "\nSuccessfully built" $(TARGETS)

%_unittest.o: %_unittest.cpp $(SRC_DIR)/%.h $(GTEST_HEADERS)
	@echo -e "  Compiling tests...\n"
	$(CXX) $(CSTD) $(CPPFLAGS) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.h $(GTEST_HEADERS)
	@echo -e "  Compiling source...\n"
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CSTD) $(CPPFLAGS) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@

# Builds the GoogleTest Framework library only if the source has been changed.

gtest_main.a: gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

gtest.a: gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.o: $(GTEST_SRCS_)
	$(CXX) $(CSTD) $(CPPFLAGS) $(CXXFLAGS) -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest_main.cc

gtest-all.o: $(GTEST_SRCS_)
	@echo -e "\n  Building library...\n"
	$(CXX) $(CSTD) $(CPPFLAGS) $(CXXFLAGS) -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest-all.cc

clean:
	@echo -e "  Cleaning...\n"; 
	rm -rf gtest.a gtest_main.a *.o $(TARGETS) 

# Necessary to explicitly tell make that "clean" isn't associated with a file.
.PHONY: all buildtests clean 
