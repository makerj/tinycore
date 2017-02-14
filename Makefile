.PHONY: clean

all:
	mkdir -p build/obj
	cd build/obj && gcc -std=gnu99 -I"../../include" -O2 -c ../../src/*.c
	ar rcs build/libtinycore.a build/obj/*.o

clean:
	rm -rf build
