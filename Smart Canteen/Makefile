# Makefile for Smart Canteen System

# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Directories
SRCDIR = src
HEADERDIR = header
TEXTDIR = Text_files

# Source files
SOURCES = $(SRCDIR)/main.cpp \
          $(SRCDIR)/MenuManager.cpp \
          $(SRCDIR)/OrderManager.cpp \
          $(SRCDIR)/SalesManager.cpp \
          $(SRCDIR)/Reports.cpp \
          $(SRCDIR)/AdminPanel.cpp \
          $(SRCDIR)/ClientPanel.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Target executable
TARGET = smart_canteen

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(HEADERDIR) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

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

# Build and run
build-run: setup $(TARGET) run

.PHONY: all clean run setup build-run