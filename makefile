# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99

# Executable name
EXEC = a4

# Source files
SRCS = graph_functions.c main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = graph.h

# Default target
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJS)
    $(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.c $(HEADERS)
    $(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
    rm -f $(OBJS) $(EXEC)

# Phony targets
.PHONY: all clean