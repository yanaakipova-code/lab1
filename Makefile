CC = gcc
CFLAGS = -Wall -Wextra -I. -g
AR = ar
ARFLAGS = rcs

SRC_DIR = .
OBJ_DIR = obj
BUILD_DIR = build

LIB = $(BUILD_DIR)/libdynamicarray.a
TARGET = $(BUILD_DIR)/program.exe

LIB_SRCS = DynamicArray.c \
           StringType.c \
           FuncType.c \
           IntType.c

MAIN_SRCS = main.c \
            main_basic.c \
            intr.c

LIB_OBJS = $(LIB_SRCS:%.c=$(OBJ_DIR)/%.o)
MAIN_OBJS = $(MAIN_SRCS:%.c=$(OBJ_DIR)/%.o)

HEADERS = ArrayEror.h \
          TypeInfo.h \
          DynamicArray.h \
          StringType.h \
          FuncType.h \
          IntType.h \
          main_basic.h \
          intr.h

.PHONY: all clean run

all: $(TARGET)

$(LIB): $(LIB_OBJS)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(TARGET): $(MAIN_OBJS) $(LIB)
	$(CC) $(CFLAGS) $(MAIN_OBJS) -L$(BUILD_DIR) -ldynamicarray -o $(TARGET)

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET)

clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)