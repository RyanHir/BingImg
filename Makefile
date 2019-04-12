bing: main.cpp
	g++ $$(curlpp-config --libs --cflags) main.cpp -o bing --std=gnu++17
