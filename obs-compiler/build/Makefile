CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../include
SRCDIR = ../src
OBJDIR = obj
BINDIR = ../binaries

# Source files (all .c recursively)
SOURCES = $(wildcard $(SRCDIR)/*.c) \
          $(wildcard $(SRCDIR)/utils/*.c) \
          $(wildcard $(SRCDIR)/icds/*.c)

# Object files (mirror directory structure)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Binary name
TARGET = $(BINDIR)/obs-compiler

# Default target
all: $(TARGET)

# Create directories
$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/utils
	mkdir -p $(OBJDIR)/icds

$(BINDIR):
	mkdir -p $(BINDIR)

# Build the binary
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compile any .c file in src or subdirectories to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Install dependencies (for Ubuntu/Debian)
install-deps:
	sudo apt-get update
	sudo apt-get install -y build-essential

# Run the compiler
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean install-deps run
