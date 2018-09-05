gcc -c $1.c
gcc -o $1 $1.o
rm $1.o
