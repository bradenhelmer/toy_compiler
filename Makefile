all:
	clang++ -g -O3 *.cpp -o compiler.o `llvm-config --cxxflags --libs --ldflags` -lncurses -lz
test:
	echo 'int do_math(int a) { int x = a * 5 + 3 } do_math(10)' | ./compiler.o
