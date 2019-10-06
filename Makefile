CC = g++
OBJ = main.o attacks.o non1loop.o non1logic.o bullet.o enemybullet.o star.o texturemanager.o junko.o healthbar.o bomb.o reimu.o reimubomb.o reimubullet.o collisionDetection.o junkoBullet.o 
INCLUDE = -Iinclude
LINKERS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_ttf 
OFLAGS = -std=c++98 -Wall -Wshadow --pedantic -Wvla -Werror  -c -g 2> gccmessages
CFLAGS =-std=c++98 -Wall -Wshadow --pedantic  -Wvla -Werror  -g -o 2> gccmessages
OUTPUT = Game
VAL = valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --log-file=memcheck.txt

run: game
	./$(OUTPUT)
gdb: game
	gdb $(OUTPUT) 
debug: game
	$(VAL) ./$(OUTPUT)
game: $(OBJ)
	$(CC) $(OBJ) $(INCLUDE) $(LIB) $(LINKERS) $(CFLAGS) $(OUTPUT)
attacks.o: attacks.cpp include/attacks.h include/non1loop.h
	$(CC) attacks.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS)
main.o: main.cpp include/attacks.h
	$(CC) main.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS)
non1loop.o: non1loop.cpp  include/non1loop.h include/non1logic.h
	$(CC) non1loop.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS)
non1logic.o: non1logic.cpp include/non1logic.h include/bullet.h include/enemybullet.h include/star.h include/junko.h include/healthbar.h include/texturemanager.h
	$(CC) non1logic.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS)
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
bomb.o: bomb.cpp include/bomb.h 
	$(CC) bomb.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS)  
reimubomb.o: reimubomb.cpp include/reimu.h include/bomb.h include/reimubomb.h
	$(CC) reimubomb.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS) 
reimubullet.o: reimubullet.cpp include/reimu.h include/reimu.h include/bullet.h 
	$(CC) reimubullet.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS) 
collisionDetection.o: collisionDetection.cpp include/reimu.h include/collisionDetection.h include/junko.h
	$(CC) collisionDetection.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS) 
junkoBullet.o: junkoBullet.cpp include/bullet.h include/enemyBullet.h include/junko.h
	$(CC) junkoBullet.cpp $(INCLUDE) $(LIB) $(LINKERS) $(OFLAGS) 
clean:
	rm -f $(OUTPUT) $(OBJ) *~
