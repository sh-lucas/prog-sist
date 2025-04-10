make:
	@g++ -std=c++20 -o ./.a.tmp ./src/*.cpp
	@./.a.tmp input.asm
	@rm .a.tmp

