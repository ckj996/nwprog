echoclient: echoclient.c lib/rio.o lib/inopen.o
	gcc -o echoclient echoclient.c lib/inopen.o lib/rio.o -Wall

echoserver: echoserver.c lib/rio.o lib/inopen.o
	gcc -o echoserver echoserver.c lib/inopen.o lib/rio.o -Wall

lib/rio.o: lib/rio.c lib/rio.h
	gcc -c -o lib/rio.o lib/rio.c -Wall

lib/inopen.o: lib/inopen.c lib/inopen.h
	gcc -c -o lib/inopen.o lib/inopen.c -Wall
