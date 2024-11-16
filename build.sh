gcc -c ./src/lib/convolve.c -o ./build/convolve.o
ar rcs ./build/libconvolve.a ./build/convolve.o
gcc ./src/main.c -L./build -lconvolve -o ./main
