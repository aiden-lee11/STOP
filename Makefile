# Makefile to handle CMake build process + fetch NYT Strands JSON

.PHONY: all clean configure build run fetch help

# Get today's date
DATE := $(shell date +%Y-%m-%d)
URL := https://www.nytimes.com/svc/strands/v2/$(DATE).json
JSON := strands.json

# Default target
all: fetch build

# Fetch today's strands.json
fetch:
	@echo "Fetching Strands puzzle for $(DATE)..."
	@curl -s "$(URL)" -o $(JSON) || echo "⚠️ Failed to fetch puzzle"

# Create build directory and configure cmake
configure:
	@echo "Configuring CMake..."
	@mkdir -p build
	@cd build && cmake ..

# Build the project (CMake will copy strands.json into build/)
build: configure
	@echo "Building project..."
	@cd build && cmake --build .

# Clean build artifacts
clean:
	@echo "Cleaning build directory..."
	@rm -rf build
	@rm -f main
	@rm -f $(JSON)

# Run the executable (fetch puzzle first)
run: fetch build
	@if [ -f "./build/main" ]; then \
		echo "Running ./build/main..."; \
		./build/main; \
	else \
		echo "Error: ./build/main not found. Build may have failed."; \
	fi

# Show available targets
help:
	@echo "Available targets:"
	@echo "  all (default) - Fetch puzzle, configure, and build the project"
	@echo "  fetch         - Download today's strands.json"
	@echo "  configure     - Create build directory and run cmake"
	@echo "  build         - Build the project"
	@echo "  clean         - Remove build directory, executable, and puzzle JSON"
	@echo "  run           - Fetch puzzle, build, and run the executable"
