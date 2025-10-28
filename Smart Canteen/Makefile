# Makefile for Smart Canteen System

# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Directories
TEXTDIR = Text_files

# Executables
ADMIN_TARGET = admin_portal
CLIENT_TARGET = client_portal

# Source files
ADMIN_SOURCE = admin_portal.cpp
CLIENT_SOURCE = client_portal.cpp

# Default target - build both portals
all: $(ADMIN_TARGET) $(CLIENT_TARGET)

# Build admin portal
$(ADMIN_TARGET): $(ADMIN_SOURCE) common.h
	$(CXX) $(CXXFLAGS) $(ADMIN_SOURCE) -o $(ADMIN_TARGET)

# Build client portal
$(CLIENT_TARGET): $(CLIENT_SOURCE) common.h
	$(CXX) $(CXXFLAGS) $(CLIENT_SOURCE) -o $(CLIENT_TARGET)

# Clean build files
clean:
	rm -f $(ADMIN_TARGET) $(CLIENT_TARGET)

# Run admin portal
run-admin: $(ADMIN_TARGET)
	./$(ADMIN_TARGET)

# Run client portal
run-client: $(CLIENT_TARGET)
	./$(CLIENT_TARGET)

# Create necessary directories and files if they don't exist
setup:
	@if [ ! -d "$(TEXTDIR)" ]; then mkdir -p $(TEXTDIR); fi
	@if [ ! -f "$(TEXTDIR)/menu.txt" ]; then \
		echo "Burger,250" > $(TEXTDIR)/menu.txt; \
		echo "Pizza,450" >> $(TEXTDIR)/menu.txt; \
		echo "Fries,150" >> $(TEXTDIR)/menu.txt; \
		echo "Sandwich,180" >> $(TEXTDIR)/menu.txt; \
		echo "Coffee,120" >> $(TEXTDIR)/menu.txt; \
		echo "Tea,80" >> $(TEXTDIR)/menu.txt; \
		echo "Setup complete: menu.txt created with sample data"; \
	fi
	@if [ ! -f "$(TEXTDIR)/sales.txt" ]; then \
		touch $(TEXTDIR)/sales.txt; \
		echo "Setup complete: sales.txt created"; \
	fi

# Install (copy executables to a bin directory if needed)
install: all
	@echo "Installation complete. Run './admin_portal' or './client_portal'"

# Help target
help:
	@echo "Smart Canteen System - Makefile Help"
	@echo "====================================="
	@echo "Available targets:"
	@echo "  all         - Build both admin and client portals"
	@echo "  admin_portal - Build only admin portal"
	@echo "  client_portal - Build only client portal"
	@echo "  run-admin   - Build and run admin portal"
	@echo "  run-client  - Build and run client portal"
	@echo "  clean       - Remove executable files"
	@echo "  setup       - Create Text_files directory and sample data"
	@echo "  install     - Build and install both portals"
	@echo "  help        - Show this help message"

.PHONY: all clean run-admin run-client setup install help
		touch $(TEXTDIR)/sales.txt; \
		echo "Setup complete: sales.txt created"; \
	fi

# Build and run
build-run: setup $(TARGET) run

.PHONY: all clean run setup build-run