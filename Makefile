CPP = g++
CPPFLAGS = -Wall -g -Werror

frupal: frupal.cpp
	$(CPP) $(CPPFLAGS) -o frupal player.cpp frupal.cpp -lncurses

clean:
	-rm -f frupal
