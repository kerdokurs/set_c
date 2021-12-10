include ../common.mk

OBJS=set.o
BINS=test

all: $(BINS)

test: test.c $(OBJS)
	$(CC) $(CFLAGS) -O2 -o $@ $< $(OBJS)

clean:
	rm -rf $(OBJS) $(BINS)
