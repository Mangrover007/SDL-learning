OBJECTS=build/LTexture.o build/LEntity.o build/LDot.o

build/template.out: $(OBJECTS) src/main.cpp
	g++ \
	-lSDL2 -lSDL2_image -lSDL2_ttf \
	$(OBJECTS) \
	src/main.cpp \
	-o build/template.out

# Because I'm just producing object files, I don't need to link the
# libraries alongisde the object files.
build/LTexture.o: include/LTexture.h src/LTexture.cpp
	g++ -c -I./include/ src/LTexture.cpp -o build/LTexture.o

build/LEntity.o: include/LEntity.h src/LEntity.cpp build/LTexture.o
	g++ -c -I./include/ src/LEntity.cpp -o build/LEntity.o

build/LDot.o: include/LDot.h src/LDot.cpp build/LEntity.o
	g++ -c -I./include/ src/LDot.cpp -o build/LDot.o

# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile
# https://stackoverflow.com/questions/46515755/exactly-what-is-a-symbol-reference-in-an-object-file

