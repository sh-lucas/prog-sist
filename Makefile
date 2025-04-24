make:
# compiles and run the mounter
	@g++ -std=c++20 -o ./.a.tmp ./mount/*.cpp
	@./.a.tmp input.asm
	@rm .a.tmp
# reads the bytes generated to cout
	@./readbytes ./output.bin
# compiles and run the virtual machine
	@g++ -std=c++20 -o ./.b.tmp ./machine/*.cpp
	@./.b.tmp output.bin
	@rm .b.tmp
