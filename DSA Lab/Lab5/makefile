compileAll	:	insert.o	driver.o
	gcc insert.o driver.o
driver.o	:	driver.c	insert.h
	gcc -c driver.c
insert.o	:	insert.c	insert.h
	gcc -c insert.c