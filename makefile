# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -std=c99 -pedantic

# Executable name
EXEC = a4

# Source files
SRCS = graph_functions.c main.c

# Default target
all: $(EXEC)

# Link source files to create the executable
$(EXEC): $(SRCS)
    $(CC) $(CFLAGS) -o $@ $(SRCS)

# Clean up build files
clean:
    rm -f $(EXEC)

# Phony targets
.PHONY: all clean