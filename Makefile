# Compiler and compile options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude

# Directories
SRCDIR = src
BINDIR = bin

# Files and targets
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
TARGET = $(BINDIR)/my_program

# Default target
all: $(TARGET)

# Compile and link source files into a binary
$(TARGET): $(SOURCES) | $(BINDIR)
	@$(CXX) $(CXXFLAGS) $^ -o $@

# Create the bin directory if it doesn't exist
$(BINDIR):
	@mkdir -p $(BINDIR)

# Clean up
clean:
	@rm -f $(TARGET)
	@rm -rf $(BINDIR)/*  # This line ensures the bin directory is cleaned up as well

# Declare non-file targets
.PHONY: all clean
