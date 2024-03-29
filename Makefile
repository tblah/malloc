OUTNAME = mallocTester
COMPFLAGS = -g -Wall -DDEBUG -DSECURE -std=c99

$(OUTNAME): main.o myMalloc.o myFree.o createFreeNode.o
	gcc $(COMPFLAGS) -o $@ main.o myMalloc.o myFree.o createFreeNode.o

main.o: main.c myMalloc.h
	gcc $(COMPFLAGS) -o $@ -c main.c 

myFree.o: myFree.c freeNode.h createFreeNode.h
	gcc $(COMPFLAGS) -o $@ -c myFree.c 

myMalloc.o: myMalloc.c freeNode.h createFreeNode.h
	gcc $(COMPFLAGS) -o $@ -c myMalloc.c

createFreeNode.o: createFreeNode.c freeNode.h
	gcc $(COMPFLAGS) -o $@ -c createFreeNode.c

# requirement to supress errors from rm
clean: $(OUTNAME) myFree.o myMalloc.o createFreeNode.o main.o
	rm $(OUTNAME) myFree.o myMalloc.o main.o createFreeNode.o
