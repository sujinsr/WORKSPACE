# I know this is world worst make file ever written.
# I dont have knowledge to write good makefile i managed to write this makefile
# with the knowledge i had.

all: sample1 sample2 sample3 sample4

sample1:
	gcc -o test/sample1 test/sample1.c leak_check.c
sample2:
	gcc -o test/sample2 test/sample2.c leak_check.c
sample3:
	gcc -o test/sample3 test/sample3.c leak_check.c
sample4:
	gcc -o test/sample4 test/sample4.c leak_check.c
	
run:
	test/sample1 
	test/sample2
	test/sample3
	test/sample4

clean:
	rm test/sample1 test/sample2 test/sample3 test/sample4