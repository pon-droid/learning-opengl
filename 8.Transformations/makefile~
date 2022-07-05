PKGS=glfw3
CFLAGS=-Wall -Wno-pedantic -std=c++14 `pkg-config --cflags --static $(PKGS)`
LIBS=`pkg-config --libs --static $(PKGS)`

gl: main.cpp
	$(CXX) $(CFLAGS) -o gl main.cpp $(LIBS)
