g++  main.cpp -o bin/main.o

g++ -fPIC -o ping.so -fPIC bin/ping.cpp
g++ -fPIC -o pong.so -fPIC bin/pong.cpp
g++ -shared   bin/ping.o bin/pong.o -o bin/pingpong.so

g++ bin/main.o ./libcalc.so -lm


