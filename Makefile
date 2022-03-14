tracker.x: tracker.o
	g++ -std=c++11 -o tracker.x tracker.o

tracker.o: tracker.cpp
	g++ -std=c++11 -c tracker.cpp

clean:
	rm tracker.x tracker.o
