APP_NAME = Minecraft
CC = clang++

SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj

INC := -Iinclude
INC += -Isrc
INC += -I/opt/homebrew/include

LIBS := /opt/homebrew/lib/libGLEW.2.2.0.dylib
LIBS += /opt/homebrew/lib/libglfw.3.3.dylib

FW := -framework OpenGL

CFLAGS := -Wall -g -MMD

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
SRCS += $(wildcard $(SRC_DIR)/*/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

OBJ_SUBDIR := $(dir $(OBJS))
$(shell mkdir -p $(OBJ_SUBDIR))

.PHONY: all clean run

TARGET := $(BIN_DIR)/$(APP_NAME)

run: $(TARGET)
	$(TARGET)

-include $(DEPS)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(INC) $(LIBS) $(FW)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) 
	$(CC) -o $@ -c $< $(CFLAGS) $(INC)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(DEPS_DIR) $(TARGET)
