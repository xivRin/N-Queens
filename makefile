NQueens:
	g++ NQueens.cpp -g -o main
run: main
	./main
gdb: main
	gdb ./main
valgrind: main
	valgrind ./main
clean: 
	rm main
