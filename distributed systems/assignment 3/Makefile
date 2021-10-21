all: server client

server: server.cpp graph.hpp disjoint_sets.hpp
	g++ server.cpp -Irpclib/include rpclib/build/librpc.a -std=c++17 -pthread -o server -O3

client: client.cpp
	g++ client.cpp -Irpclib/include rpclib/build/librpc.a -std=c++17 -pthread -o client -O3

clean:
	rm server client