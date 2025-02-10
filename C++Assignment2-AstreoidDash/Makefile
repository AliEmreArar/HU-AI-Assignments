CC = g++
CFLAGS = -std=c++11 -g
LDFLAGS =

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
HEADER_GCH = $(wildcard *.gch)

all: AsteroidDash

AsteroidDash: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) -o $@

clean:
	rm -f $(TESTS) $(HEADER_GCH)