CC = gcc
CFLAGS = -Wall -Wextra -I. -I.. -D_XOPEN_SOURCE_EXTENDED
LDFLAGS = -Wl,--wrap=abort
LDLIBS = -lm

EXE_FILES = *.exe
OBJ_FILES = *.o
LIB_FILES = *.a

PROJ_SRCS = ../DynamicArray.c \
            ../StringType.c \
            ../FuncType.c \
            ../IntType.c \
            ../main_basic.c

FRAME_SRCS = assertions.c testing.c mork.c
SRCS = $(PROJ_SRCS) $(FRAME_SRCS)

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

TARGET = test_all.exe

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(TEST_SRCS) $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

run: $(TARGET)
	$(TARGET)

clean:
	rm -f $(EXE_FILES) $(OBJ_FILES) $(LIB_FILES)