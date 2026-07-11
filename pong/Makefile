CXX = clang++
CXXFLAGS = $(shell pkg-config --cflags sfml-graphics sfml-window sfml-system)
LDFLAGS = $(shell pkg-config --libs sfml-graphics sfml-window sfml-system)

pong: idk.cpp
		$(CXX) idk.cpp -o pong $(CXXFLAGS) $(LDFLAGS)

run: pong
		./pong

clean:
		rm -f pong
