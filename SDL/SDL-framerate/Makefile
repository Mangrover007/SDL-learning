OBJECTS=build/LTexture.o build/LTimer.o

build/framerate.out: $(OBJECTS) src/main.cpp
	g++ \
	-lSDL2 -lSDL2_image -lSDL2_ttf \
	$(OBJECTS) \
	src/main.cpp \
	-o build/framerate.out

# Because I'm just producing object files, I don't need to link the
# libraries alongisde the object files.
build/LTexture.o: include/LTexture.h src/LTexture.cpp
	g++ -c -I./include/ src/LTexture.cpp -o build/LTexture.o

build/LTimer.o: include/LTimer.h src/LTimer.cpp
	g++ -c -I./include/ src/LTimer.cpp -o build/LTimer.o

# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile
# https://stackoverflow.com/questions/46515755/exactly-what-is-a-symbol-reference-in-an-object-file

