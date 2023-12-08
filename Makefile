APP_NAME = Minecraft
CC = clang++

SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/obj

INC := -Iinclude
INC += -I/opt/homebrew/include

LIBS := /opt/homebrew/lib/libGLEW.2.2.0.dylib
LIBS += /opt/homebrew/lib/libglfw.3.3.dylib

FW := -framework OpenGL

CFLAGS := -Wall -g

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean run

TARGET := $(BIN_DIR)/$(APP_NAME)

run: $(TARGET)
	$(TARGET)

-include $(DEPS)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(INC) $(LIBS) $(FW)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) -o $@ -c $< -MMD $(CFLAGS) $(INC)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm $(OBJ_DIR)/*.o $(TARGET)
