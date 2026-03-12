CC = gcc
CFLAGS = -Wall -Wextra -I.
AR = ar
ARFLAGS = rcs

LIB_SRCS = DynamicArray.o \
	StringType.o \
	FuncType.o \
	IntType.o \
	 main_basic.o

LIB_OBJS = $(LIB_SRCS:.c=.o)
MAIN_SRC = main.c

LIB_NAME = libdynamicarray.a
TARGET = program.exe

.PHONY = all clean run lib

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(MAIN_SRC) -o $@ $(LIB_NAME) 

lib: $(LIB_NAME)

$(LIB_NAME): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET)

clean: 
	del /q $(TARGET) *.o *.a