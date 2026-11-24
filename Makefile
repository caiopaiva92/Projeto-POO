# Compilação alternativa ao CMake. Tudo é gerado dentro de build/.
CXX      ?= g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Iinclude

SRC_DIR   := src
BUILD_DIR := build
TARGET    := $(BUILD_DIR)/app

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)