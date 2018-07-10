#mainメソッド

ping: main.o ping.o checksum.o brege.o
	gcc -o ping main.o ping.o checksum.o brege.o

main: main.c
	gcc -c main.c

brege.o: module/brege.c
	gcc -c module/brege.c

checksum.o: module/checksum.c
	gcc -c module/checksum.c

ping.o: module/ping.c
	gcc -c module/ping.c
