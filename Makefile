OUTNAME = mallocTester
COMPFLAGS = -g -Wall -DDEBUG -DSECURE -std=c99

$(OUTNAME): main.c myMalloc.o myMalloc.h myFree.o
	gcc $(COMPFLAGS) -o main.o -c main.c 
	gcc $(COMPFLAGS) -o $@ main.o myMalloc.o myFree.o

myFree.o: myFree.c
	gcc $(COMPFLAGS) -o $@ -c myFree.c

myMalloc.o: myMalloc.c
	gcc $(COMPFLAGS) -o $@ -c myMalloc.c

# requirement to supress errors from rm
clean: $(OUTNAME) myFree.o myMalloc.o
	rm $(OUTNAME) myFree.o myMalloc.o main.o
