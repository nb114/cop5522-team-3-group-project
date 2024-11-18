CC=gcc
CFLAG= -Wall -I. -O0
OPTFLAG= -fopenmp -Wall -I. -O3

TARGETS=unoptimized opt1# add your target here

all: $(TARGETS)

unoptimized: unoptimized.o microtime.o
	$(CC) -o $@ $^

unoptimized.o: unoptimized.c microtime.h
	$(CC) $(CFLAG) -c $<

microtime.o: microtime.c microtime.h
	$(CC) $(CFLAG) -c $<



opt1: opt1.o microtime.o
	$(CC) $(OPTFLAG) -o $@ $^

opt1.o: opt1.c microtime.h
	$(CC) $(OPTFLAG) -c $<


# Add your rules here.
# Example: code in opt1.c

# opt1: opt1.o microtime.o
# 	$(CC) -o $@ $^

# opt1.o: opt1.c microtime.h
# 	$(CC) $(CFLAG) -c $<


clean:
	rm -f *.o *~ core $(TARGETS)
