CC = gcc
sfolder = src
ofolder = bin
flags = -lpthread -g

keywordSearch: main.o keyword.o output.o
	${CC} ${ofolder}/main.o ${ofolder}/keyword.o ${ofolder}/output.o -o ${ofolder}/keywordSearch.out ${flags}
	./${ofolder}/keywordSearch.out testcases/t1.txt testcases/t2.txt testcases/t3.txt testcases/t4.txt testcases/t5.txt testcases/t6.txt

main.o: src/main.c
	${CC} -c ${sfolder}/main.c -o ${ofolder}/main.o ${flags}

keyword.o: src/keyword.c
	${CC} -c ${sfolder}/keyword.c -o ${ofolder}/keyword.o ${flags}

output.o: src/output.c
	${CC} -c ${sfolder}/output.c -o ${ofolder}/output.o ${flags}

clean:
	rm -f ./${ofolder}/*.out ./${ofolder}/*.o