# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Source files
TREE_NODE_SRC = $(SRC_DIR)/Tree_Node.cpp
TREE_SRC = $(SRC_DIR)/Tree.cpp
ENCODER_SRC = $(SRC_DIR)/Encoder.cpp
DECODER_SRC = $(SRC_DIR)/Decoder.cpp
MAIN_ENCODE_SRC = $(SRC_DIR)/main_encode.cpp
MAIN_DECODE_SRC = $(SRC_DIR)/main_decode.cpp

# Object files
TREE_NODE_OBJ = $(BUILD_DIR)/Tree_Node.o
TREE_OBJ = $(BUILD_DIR)/Tree.o
ENCODER_OBJ = $(BUILD_DIR)/Encoder.o
DECODER_OBJ = $(BUILD_DIR)/Decoder.o
MAIN_ENCODE_OBJ = $(BUILD_DIR)/main_encode.o
MAIN_DECODE_OBJ = $(BUILD_DIR)/main_decode.o

# Executables
ENCODE_EXEC = $(BIN_DIR)/encoder
DECODE_EXEC = $(BIN_DIR)/decoder

# Targets
all: $(ENCODE_EXEC) $(DECODE_EXEC)

# Encoding executable
$(ENCODE_EXEC): $(TREE_NODE_OBJ) $(TREE_OBJ) $(ENCODER_OBJ) $(MAIN_ENCODE_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Decoding executable
$(DECODE_EXEC): $(TREE_NODE_OBJ) $(TREE_OBJ) $(DECODER_OBJ) $(MAIN_DECODE_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile Tree_Node.cpp
$(TREE_NODE_OBJ): $(SRC_DIR)/Tree_Node.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile Tree.cpp
$(TREE_OBJ): $(SRC_DIR)/Tree.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile Encoder.cpp
$(ENCODER_OBJ): $(SRC_DIR)/Encoder.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile Decoder.cpp
$(DECODER_OBJ): $(SRC_DIR)/Decoder.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile main_encode.cpp
$(MAIN_ENCODE_OBJ): $(SRC_DIR)/main_encode.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile main_decode.cpp
$(MAIN_DECODE_OBJ): $(SRC_DIR)/main_decode.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up
clean:
	rm -f $(BUILD_DIR)/*.o $(BIN_DIR)/*

# Create build and bin directories if they don't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

.PHONY: all clean
