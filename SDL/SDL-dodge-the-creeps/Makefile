OBJECTS=build/LTexture.o build/LPlayer.o build/LTimer.o build/LButton.o

build/dodge-the-creeps.out: $(OBJECTS) src/main.cpp
	g++ \
	-lSDL2 -lSDL2_image -lSDL2_ttf \
	$(OBJECTS) \
	src/main.cpp \
	-o build/dodge-the-creeps.out

# Because I'm just producing object files, I don't need to link the
# libraries alongisde the object files.
build/LTexture.o: include/LTexture.h src/LTexture.cpp
	g++ -c -I./include/ src/LTexture.cpp -o build/LTexture.o

build/LButton.o: include/LButton.h src/LButton.cpp
	g++ -c -I./include/ src/LButton.cpp -o build/LButton.o

build/LTimer.o: include/LTimer.h src/LTimer.cpp
	g++ -c -I./include/ src/LTimer.cpp -o build/LTimer.o

build/LPlayer.o: include/LPlayer.h src/LPlayer.cpp
	g++ -c -I./include/ src/LPlayer.cpp -o build/LPlayer.o

# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile
# https://stackoverflow.com/questions/46515755/exactly-what-is-a-symbol-reference-in-an-object-file

