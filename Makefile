CC = g++
CFLAGS = -Wall -w
PROG = carrom

SRCS = main.cpp Board.cpp Coin.cpp Player.cpp Striker.cpp
LIBS = -lglut -lGL -lGLU

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
