CC = gcc
CFLAGS = -I/opt/homebrew/opt/sdl2/include
LDFLAGS = -L/opt/homebrew/opt/sdl2/lib -lSDL2

TARGET = sdl_test
SRC = main.c funcs.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)