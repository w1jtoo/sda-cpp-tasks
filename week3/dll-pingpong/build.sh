# OS: Arch Linux

g++ -c -Wall -Werror -fpic -o ./bin/ping.o ping.cpp
g++ -c -Wall -Werror -fpic -o ./bin/pong.o pong.cpp

g++  -shared -Wl,--out-implib=./bin/pong.lib -o ./bin/libpong.so ./bin/pong.o
g++  -shared -Wl,--out-implib=./bin/ping.lib -o ./bin/libping.so ./bin/ping.o

g++  -shared -Wl,--out-implib=./bin/pong.lib -o ./bin/libpong.so ./bin/pong.o ./bin/ping.lib
g++  -shared -Wl,--out-implib=./bin/ping.lib -o ./bin/libping.so ./bin/ping.o ./bin/pong.lib

sudo cp ./bin/libping.so /usr/lib
sudo chmod 755 /usr/lib/libping.so 

sudo cp ./bin/libpong.so /usr/lib
sudo chmod 755 /usr/lib/libpong.so 

sudo ldconfig

g++ -Wall -o result.elf main.cpp -lping -lpong

export LD_LIBRARY_PATH=/home/wanadoo/programming/cpp/sda-cpp-tasks/week3/dll-pingpong/bin:$Ld_LIBRARY_PATH

chmod 755 ./result.elf
./result.elf

unset LD_LIBRARY_PATH
sudo rm /usr/lib/libping.so
sudo rm /usr/lib/libpong.so

# Or just...
# DIR=$(pwd)/bin
# g++ -L$DIR -Wl,-rpath=$DIR -Wall -g -pedantic -lping -lpong main.cpp -o ./bin/main.elf
