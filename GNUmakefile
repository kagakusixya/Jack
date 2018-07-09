#mainメソッド

ping: main.o ping.o checksum.o
	gcc -o ping main.o ping.o checksum.o

main: main.c
	gcc -c main.c

checksum.o: module/checksum.c
	gcc -c module/checksum.c

ping.o: module/ping.c
	gcc -c module/ping.c
