OBJECTS=build/LTexture.o build/LButton.o

build/mouse-events.out: $(OBJECTS)
	g++ \
	-lSDL2 -lSDL2_image -lSDL2_ttf \
	$(OBJECTS) \
	src/main.cpp \
	-o build/mouse-events.out

# Because I'm just producing object files, I don't need to link the
# libraries alongisde the object files.
build/LTexture.o:
	g++ -c -I./include/ src/LTexture.cpp -o build/LTexture.o

build/LButton.o:
	g++ -c -I./include/ src/LButton.cpp -o build/LButton.o

# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile
# https://stackoverflow.com/questions/46515755/exactly-what-is-a-symbol-reference-in-an-object-file

