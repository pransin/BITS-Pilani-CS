compResMS	:	driver.o	recMS.o	merge.o
	gcc driver.o merge.o recMS.o -o recMS
compIterMS	:	driver.o	iterMS.o	merge.o
	gcc driver.o merge.o iterMS.o -o iterMS
runRecMS	:	recMS
	./recMS
runIterMS	:	iterMS
	./iterMS
driver.o	:	driver.c	mergeSort.h
	gcc -c driver.c
recMS.o	:	recMS.c	merge.h
	gcc -c recMS.c
iterMS.o	:	iterMS.c	merge.h
	gcc -c iterMS.c
merge.o	:	merge.c	merge.h
	gcc -c merge.c
