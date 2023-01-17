all:	native wasm

wasm:
	emcc sdl_test.c -sUSE_SDL=2 -O3 -o sdl_test.html

native:
	gcc sdl_test.c -o sdl_test -lSDL2 -O3

serve:	wasm
	python3 -m http.server


clean:
	rm sdl_test
	rm *.wasm *.js *.html