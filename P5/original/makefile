CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
EXECUTABLE = main

# Lista de archivos fuente
SRCS = $(wildcard $(SRC_DIR)/*.cc)

# Objetos
OBJS = $(SRCS:$(SRC_DIR)/%.cc=$(BUILD_DIR)/%.o)

# Dependencias
DEPS = $(OBJS:.o=.d)

# Compilación
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -MMD -MP -c $< -o $@

# Enlazado
$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)

# Incluyendo dependencias
-include $(DEPS)
