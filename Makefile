all: zhalka zhalka.wasm

lib/sdl/libsdl.a:
	make -C lib/sdl

SDL_SRCS=sdl_renderer.cpp \
			main_sdl.cpp
SDL_HDRS=sdl_renderer.h

WASM_SRCS=wasm_renderer.cpp \
			main_wasm.cpp
WASM_HDRS=wasm_renderer.h

zhalka: main_sdl.cpp game.h game.cpp renderer.cpp ${SDL_SRCS} ${SDL_HDRS} lib/sdl/libsdl.a Makefile string.h string.cpp
	clang++ -g ${SDL_SRCS} game.cpp renderer.cpp \
		-g \
		-o zhalka \
		-lSDL2 \
		-lGL \
		-I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu/c++/11 -L /usr/lib/gcc/x86_64-linux-gnu/11 \
		-L./lib/sdl -lsdl

zhalka.wasm: main_wasm.cpp game.h game.cpp renderer.cpp renderer.h wasm_renderer.h wasm_renderer.cpp memory.h memory.cpp Makefile string.cpp string.h
	clang++ -O3 -std=c++20 -c main_wasm.cpp --target=wasm32 -mbulk-memory
	clang++ -O3 -c game.cpp --target=wasm32 -mbulk-memory
	clang++ -O3 -std=c++20 -c wasm_renderer.cpp --target=wasm32 -mbulk-memory
	clang++ -O3 -c renderer.cpp --target=wasm32 -mbulk-memory
	clang++ -O3 -c memory.cpp --target=wasm32 -mbulk-memory
	clang++ -O3 -c string.cpp --target=wasm32 -mbulk-memory
	wasm-ld --no-entry --export-all -o zhalka.wasm main_wasm.o game.o wasm_renderer.o renderer.o memory.o --allow-undefined -mwasm32

clean:
	rm .r *.o
