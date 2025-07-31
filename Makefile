CC := gcc
CFLAGS := -Wall -pedantic -O2
LDFLAGS := -L.

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(shell pwd)

.PHONY: all
all: testSorting.exe

testSorting.exe: testSorting.c libsorting.so
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) -l sorting

libsorting.so: sorting.o
	$(CC) -shared $< -o $@

sorting.o: sorting.c sorting.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

.PHONY: clean
clean:
	rm -rf *.o *.so
