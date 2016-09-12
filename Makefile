CC=gcc
CFLAGS= -c -Wall -std=gnu99
LDLIBS= -lncurses -lpthread
SOURCES=main.c tetris.c input.c menu.c blocks.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=tetris


all: $(SOURCES) $(EXECUTABLE)

debug: CFLAGS += -ggdb
debug: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LDLIBS)

#$@ = name of target, $< = name of prerequisite
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
