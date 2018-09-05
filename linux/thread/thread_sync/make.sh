g++ -c $1.cpp
g++ -o $1 $1.o -lpthread
rm $1.o
