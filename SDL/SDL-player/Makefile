OBJECTS=build/LTexture.o build/LPlayer.o

build/player-move.out: $(OBJECTS) src/main.cpp
	g++ \
	-lSDL2 -lSDL2_image -lSDL2_ttf \
	$(OBJECTS) \
	src/main.cpp \
	-o build/player-move.out

# Because I'm just producing object files, I don't need to link the
# libraries alongisde the object files.
build/LTexture.o: src/LTexture.cpp include/LTexture.h
	g++ -c -I./include/ src/LTexture.cpp -o build/LTexture.o

build/LPlayer.o: src/LPlayer.cpp include/LPlayer.h
	g++ -c -I./include/ src/LPlayer.cpp -o build/LPlayer.o

# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile
# https://stackoverflow.com/questions/46515755/exactly-what-is-a-symbol-reference-in-an-object-file

