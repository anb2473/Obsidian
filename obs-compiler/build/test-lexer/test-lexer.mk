CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../../include
SRCDIR = ../../src
OBJDIR = obj-test
BINDIR = ../../binaries
TESTDIR = ../../output_target

# Test target
.PHONY: test-lexer clean-test

# Test the lexer on the in.obs file
test-lexer: $(BINDIR)/test-lexer
	@echo "Testing lexer on $(TESTDIR)/in.obs..."
	@$(BINDIR)/test-lexer $(TESTDIR)/in.obs

# Build the test lexer
$(BINDIR)/test-lexer: $(OBJDIR)/test-lexer.o $(OBJDIR)/lexer.o $(OBJDIR)/str-utils.o
	@mkdir -p $(BINDIR)
	$(CC) $^ -o $@
	@echo "Test lexer built successfully"

# Compile test lexer main
$(OBJDIR)/test-lexer.o: test-lexer.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile lexer
$(OBJDIR)/lexer.o: $(SRCDIR)/lexer.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile string utilities
$(OBJDIR)/str-utils.o: $(SRCDIR)/utils/str-utils.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create test object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean test artifacts
clean-test:
	rm -rf $(OBJDIR)
	rm -f $(BINDIR)/test-lexer

# Show help
help:
	@echo "Available targets:"
	@echo "  test-lexer  - Build and run lexer test on in.obs file"
	@echo "  clean-test  - Clean test build artifacts"
	@echo "  help        - Show this help message"
