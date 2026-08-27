OBJECTS=build/LTexture.o build/LTimer.o
SOURCES=src/LTexture.cpp src/LButton.cpp src/main.cpp

build/timer.out: $(OBJECTS) src/main.cpp
	g++ \
	-lSDL2 -lSDL2_image -lSDL2_ttf \
	$(OBJECTS) \
	src/main.cpp \
	-o build/timer.out

# Because I'm just producing object files, I don't need to link the
# libraries alongisde the object files.
build/LTexture.o: src/LTexture.cpp
	g++ -c -I./include/ src/LTexture.cpp -o build/LTexture.o

build/LTimer.o: src/LTimer.cpp
	g++ -c -I./include/ src/LTimer.cpp -o build/LTimer.o

# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile
# https://stackoverflow.com/questions/46515755/exactly-what-is-a-symbol-reference-in-an-object-file

