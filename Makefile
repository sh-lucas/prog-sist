make:
	@g++ -std=c++20 -o ./.a.tmp ./mount/*.cpp
	@./.a.tmp input.asm
	@rm .a.tmp
	@g++ -std=c++20 -o ./.b.tmp ./machine/*.cpp
	@./.b.tmp output.bin
	@rm .b.tmp

