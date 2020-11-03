CC = gcc
CFLAGS = -g -W
INCS = -Ixxhash
LIBS = -ldl -lxxhash
APP = out/example

supp-run: build
	valgrind --gen-suppressions=all --suppressions=suppressions.sup --leak-check=full --show-leak-kinds=all ./$(APP)

nosupp-run: build
	valgrind --leak-check=full --show-leak-kinds=all ./$(APP)

noval-run: build
	./$(APP)

build:
	fbuild

clean:
	rm -f *.o
	rm -f *.app
