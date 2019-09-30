all:Source.cpp
	g++ Source.cpp -o blif
	
	
clean:
	rm -rf blif
