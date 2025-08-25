all:
	g++ -o yumiRelease yumi/main.cpp yumi/ylex.cpp

run:
	./yumiRelease
#n: main.o
	#gcc -o main main.o

#main.o: main.rs
#	rustc -g -C opt-level=z --emit=obj -C panic="abort" main.rs
