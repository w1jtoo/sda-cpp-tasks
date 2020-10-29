g++ -c -Wall -Werror -fpic -o ./bin/ping.o ping.cpp
g++ -c -Wall -Werror -fpic -o ./bin/pong.o pong.cpp

g++ -shared ./bin/ping.o -o ./bin/ping.so
g++ -shared ./bin/pong.o -o ./bin/pong.so

cp /home/w1jtoo/sda-cpp-tasks/week3/dll-pingpong/bin/ping.so /usr/lib
chmod 0755 /usr/lib/ping.so 

cp /home/w1jtoo/sda-cpp-tasks/week3/dll-pingpong/bin/pong.so /usr/lib
chmod 0755 /usr/lib/pong.so 

ldconfig

g++ -Wall -o result.elf main.cpp -lping -lpong

export LD_LIBRARY_PATH=/home/w1jtoo/sda-cpp/tasks/week3/dll-pingpong/bin:$Ld_LIBRARY_PATH

chmod 755 ./result.elf
./result.elf
