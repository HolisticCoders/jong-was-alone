if [ ! -d "obj" ]; then
    mkdir obj
fi
set -e    # if error, stop the build
g++ -Wall -Wextra -Werror -g -std=c++17 -c -I /opt/raylib/src main.cpp -o ./obj/main.o
g++ -Wall -Wextra -Werror -o main  obj/main.o -s -Wall -std=c++17 -I/opt/raylib/src -L/opt/raylib/release/libs/linux -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./main
