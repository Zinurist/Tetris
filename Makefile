CC=gcc
CFLAGS= -c -Wall -std=gnu99
LDLIBS= -lncursesw -lpthread
SOURCES=main.c tetris.c input.c menu.c blocks.c spooky.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=Tetris


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LDLIBS)


#$@ = name of target, $< = name of prerequisite
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
