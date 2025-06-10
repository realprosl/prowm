# Variables básicas
CXX := g++
STD := 20
BUILD_DIR := build
BIN_DIR := $(BUILD_DIR)/bin
SRC_DIR := src
INCLUDE_DIR := includes
EXECUTABLE := main
# Por ejemplo: LIBRARIES := opencv glfw3
LIBRARIES := x11

# Encuentra todos los .cpp en src/ y subdirectorios
SRC := $(shell find $(SRC_DIR) -name '*.cpp')

# Construye la ruta .o correspondiente para cada .cpp
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

# Flags de compilación
CXXFLAGS := -std=c++$(STD) -I$(INCLUDE_DIR) $(shell pkg-config --cflags $(LIBRARIES))
LDFLAGS := $(shell pkg-config --libs $(LIBRARIES))

# Compilación: .cpp → .o dentro de build/ (manteniendo subdirectorios)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target final
$(BIN_DIR)/$(EXECUTABLE): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# Atajo para compilar todo
all: $(BIN_DIR)/$(EXECUTABLE)

# Ejecutar el programa
run: all
	$(BIN_DIR)/$(EXECUTABLE)

# Limpiar
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean