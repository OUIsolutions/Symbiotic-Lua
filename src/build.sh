

gcc pre/main.c -o pre.o
./pre.o
gcc c/main.c -o ../final.o
rm pre.o
./../final.o