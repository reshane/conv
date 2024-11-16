gcc -c ./src/lib/convolve.c -o ./build/convolve.o
ar rcs ./build/libconvolve.a ./build/convolve.o
gcc ./src/test.c -L./build -lconvolve -o ./build/test
gcc ./src/main.c -L./build -lconvolve -o ./build/main
