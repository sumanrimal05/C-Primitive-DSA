# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Source files
SRCS = main.c dynamicArray.c

# Object files (compiling each source file to an object file)
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = dynamicArray

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove the executable and object files
clean:
	rm -f $(TARGET) $(OBJS)
