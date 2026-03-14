CC = gcc
CFLAGS = -Wall -Wextra -I. -I.. -D_XOPEN_SOURCE_EXTENDED -g
LDFLAGS = -Wl,--wrap=abort
LDLIBS = -lm

SRC_DIR = ..
OBJ_DIR = obj
TEST_DIR = .

PROJ_SRCS = $(SRC_DIR)/DynamicArray.c \
            $(SRC_DIR)/StringType.c \
            $(SRC_DIR)/FuncType.c \
            $(SRC_DIR)/IntType.c \
            $(SRC_DIR)/main_basic.c

FRAME_SRCS = assertions.c testing.c mork.c

TEST_SRCS = run_all_tests.c \
            test_dynamic_array.c \
            test_func_type.c \
            test_int_type.c \
            test_string_type.c \
            test_main_basic_1.c \
            test_map.c \
            test_where.c \
            test_reduce.c \
            test_concatenation.c \
            test_do_map.c \
            test_do_where.c \
            test_do_reduce.c \
            test_do_concatenation.c

PROJ_OBJS = $(PROJ_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
FRAME_OBJS = $(FRAME_SRCS:%.c=$(OBJ_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:%.c=$(OBJ_DIR)/%.o)

HEADERS = $(SRC_DIR)/*.h *.h

TARGET = test_all.exe

.PHONY: all clean run dirs

all: dirs $(TARGET)

dirs:
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

$(TARGET): $(PROJ_OBJS) $(FRAME_OBJS) $(TEST_OBJS)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	@echo "Тесты собраны: $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

run: $(TARGET)
	$(TARGET)

clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@if exist $(TARGET) del /q $(TARGET)