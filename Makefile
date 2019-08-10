CC = g++
OBJ = main.o gameloop.o gamelogic.o reimu.o bullet.o enemybullet.o star.o texturemanager.o junko.o healthbar.o 
INCLUDE = -Iinclude
LINKERS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_ttf 
OFLAGS = -std=c++98 -Wall -Wshadow --pedantic -Wvla -Werror  -c -g
CFLAGS =-std=c++98 -Wall -Wshadow --pedantic  -Wvla -Werror  -g -o
OUTPUT = test

test: game
	./test
gdb: game
	gdb $(OUTPUT) 
debug: game
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test 
game: $(OBJ)
	$(CC) $(OBJ) $(INCLUDE) $(LIB) $(LINKERS) $(CFLAGS) $(OUTPUT)
main.o: main.cpp include/gameloop.h
	$(CC) main.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS) 
gameloop.o: gameloop.cpp  include/gameloop.h include/gamelogic.h
	$(CC) gameloop.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS)
gamelogic.o: gamelogic.cpp include/gamelogic.h include/bullet.h include/enemybullet.h include/star.h include/junko.h include/healthbar.h include/texturemanager.h
	$(CC) gamelogic.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS)
reimu.o: reimu.cpp include/reimu.h
	$(CC) reimu.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS)
bullet.o: bullet.cpp include/bullet.h
	$(CC) bullet.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS)
enemybullet.o: enemybullet.cpp include/enemybullet.h
	$(CC) enemybullet.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS)
star.o: star.cpp include/star.h
	$(CC) star.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS)
texturemanager.o: texturemanager.cpp include/texturemanager.h
	$(CC) texturemanager.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS)
junko.o: junko.cpp include/junko.h
	$(CC) junko.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS)
healthbar.o: healthbar.cpp include/healthbar.h
	$(CC) healthbar.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS)
clean:
	rm -f $(OUTPUT) $(OBJ)
