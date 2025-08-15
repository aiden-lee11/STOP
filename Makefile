CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
SRC_DIR := src
BUILD_DIR := build
TARGET := main

# Find all source files
SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
# Generate object file paths under build/
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
# Dependency files
DEPS := $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking $@..."
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile each .cpp into .o in build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Include dependency files if they exist
-include $(DEPS)

.PHONY: all clean
