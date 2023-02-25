all:
	clang++ -g -O3 *.cpp -o parser `llvm-config --cxxflags --libs --ldflags` -lncurses -lz
