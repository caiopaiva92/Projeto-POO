# Compilação alternativa ao CMake. Tudo é gerado dentro de build/.
CXX      ?= g++
CXXFLAGS := -std=c++17 -Iinclude

# Portão de avisos da Unidade I, aplicado à biblioteca das classes
PORTAO := -Wall -Wextra -Wpedantic -Wshadow -Wold-style-cast -Wcast-align \
          -Wconversion -Wsign-conversion -Wnon-virtual-dtor -Wdouble-promotion \
          -Wformat=2 -Werror

SRC_DIR   := src
BUILD_DIR := build
LIB       := $(BUILD_DIR)/libpoo.a
TARGET    := $(BUILD_DIR)/app

LIB_SRCS := $(filter-out $(SRC_DIR)/main.cpp,$(wildcard $(SRC_DIR)/*.cpp))
LIB_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(LIB_SRCS))

.PHONY: all run clean

all: $(TARGET)

# Executável: main.cpp ligado à biblioteca
$(TARGET): $(SRC_DIR)/main.cpp $(LIB)
	$(CXX) $(CXXFLAGS) -Wall -Wextra $< -L$(BUILD_DIR) -lpoo -o $@

# Biblioteca estática com as classes
$(LIB): $(LIB_OBJS)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(PORTAO) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)