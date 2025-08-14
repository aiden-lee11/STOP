# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Target program name
TARGET = strands

# Find all .cpp files 
SOURCES = $(shell find src -name '*.cpp')

# Convert src/file.cpp → build/file.o
# $(patsubst pattern,replacement,text)
OBJECTS = $(patsubst src/%.cpp, build/%.o, $(SOURCES))

# Default target — builds the program
all: $(TARGET)

# Linking step: combine all .o files into the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation step: compile each .cpp into a .o in build/
# $< = first prerequisite (source file)
# $@ = target (object file)
build/%.o: src/%.cpp
	@mkdir -p $(dir $@)         # Create folder for object if it doesn't exist
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(TARGET) $(OBJECTS)
