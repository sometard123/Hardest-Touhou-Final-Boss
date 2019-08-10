# testing_game_linux
Junko's 3rd non-spell written in C++
#How to Play
Kill Junko while dodging all bullets to win. Player starts with 3 lives.

#Controls
*z - shoot
*arrow keys - move
*lshift/rshift - toggles hitbox
*lshift/rshift - toggles hitbox and slows movement

#Makefile Commands
make: compiles all source files, builds executable, and runs it
make gdb: compiles all source files, builds exectuable and launches executable in debug mode
make game: compiles all source files, and builds executable
make debug: builds executable and runs it while checking for memory leaks (this can be very laggy)
make clean: removes all object files and executable


