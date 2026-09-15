OBJECTS=build/LWindow.o

build/timer.out: $(OBJECTS) src/main.cpp
	g++ \
	-lSDL2 -lSDL2_image \
	$(OBJECTS) \
	src/main.cpp \
	-o build/window-events.out

# Because I'm just producing object files, I don't need to link the
# libraries alongisde the object files.
build/LWindow.o: include/LWindow.h src/LWindow.cpp
	g++ -c -I./include/ src/LWindow.cpp -o build/LWindow.o

# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile
# https://stackoverflow.com/questions/46515755/exactly-what-is-a-symbol-reference-in-an-object-file


