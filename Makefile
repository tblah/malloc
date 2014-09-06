OUTNAME = mallocTester
COMPFLAGS = -g -Wall

$(OUTNAME): main.c malloc.c malloc.h free.c
	gcc $(COMPFLAGS) -o $@ main.c malloc.c free.c

# requirement to supress errors from rm
clean: $(OUTNAME)
	rm $(OUTNAME)
