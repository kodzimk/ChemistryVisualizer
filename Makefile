CFLAGS = -Wall -std=c99
LIBS = 

build:
	$(CC) $(CFLAGS) src/*.c `sdl2-config --libs --cflags` -lm -o game $(LIBS)

run:
	./game

clean:
	rm game