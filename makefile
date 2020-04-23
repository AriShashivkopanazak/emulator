# compiles the emulator

BUILD_DIR ?= ./build
SRC_DIR ?= ./src

# myapp: main.cpp
clean: ./src/main.cpp
	g++ ./src/main.cpp -o ./build/emulator