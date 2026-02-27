TARGET = program
.PHONY: all clean
all: $(TARGET)
clean:
	rm -rf $(TARGET) *.o

main.o: main.c main_basic.h DynamicArray.h StringType.h FuncType.h IntType.h TypeInfo.h ArrayEror.h
	gcc -c -o main.o main.c

main_basic.o: main_basic.c main_basic.h DynamicArray.h StringType.h FuncType.h IntType.h TypeInfo.h ArrayEror.h
	gcc -c -o main_basic.o main_basic.c

DynamicArray.o: DynamicArray.c DynamicArray.h TypeInfo.h ArrayEror.h FuncType.h StringType.h
	gcc -c -o DynamicArray.o DynamicArray.c

StringType.o: StringType.c StringType.h TypeInfo.h ArrayEror.h
	gcc -c -o StringType.o StringType.c

FuncType.o: FuncType.c FuncType.h TypeInfo.h ArrayEror.h
	gcc -c -o FuncType.o FuncType.c

IntType.o: IntType.c IntType.h TypeInfo.h ArrayEror.h
	gcc -c -o IntType.o IntType.c

test.o: test.c main_basic.h DynamicArray.h StringType.h FuncType.h IntType.h TypeInfo.h ArrayEror.h
	gcc -c -o test.o test.c

$(TARGET): main.o main_basic.o DynamicArray.o StringType.o FuncType.o IntType.o
	gcc -o $(TARGET) main.o main_basic.o DynamicArray.o StringType.o FuncType.o IntType.o

test: test.o main_basic.o DynamicArray.o StringType.o FuncType.o IntType.o
	gcc -o test test.o main_basic.o DynamicArray.o StringType.o FuncType.o IntType.o

run-tests: test
	./test