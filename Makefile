# Simple Makefile to handle cmake build process
# This allows you to run 'make all' or just 'make' from the root directory

.PHONY: all clean configure build run help

# Default target
all: build

# Create build directory and configure cmake
configure:
	@echo "Configuring CMake..."
	@mkdir -p build
	@cd build && cmake ..

# Build the project
build: configure
	@echo "Building project..."
	@cd build && cmake --build .

# Clean build artifacts
clean:
	@echo "Cleaning build directory..."
	@rm -rf build
	@rm -f main

# Run the executable (if it exists)
run: build
	@if [ -f "./main" ]; then \
		echo "Running ./main..."; \
		./main; \
	else \
		echo "Error: ./main not found. Build may have failed."; \
	fi

# Show available targets
help:
	@echo "Available targets:"
	@echo "  all (default) - Configure and build the project"
	@echo "  configure     - Create build directory and run cmake"
	@echo "  build         - Build the project"
	@echo "  clean         - Remove build directory and executable"
	@echo "  run           - Build and run the executable"
	@echo "  help          - Show this help message"
