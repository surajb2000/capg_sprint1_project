CC = gcc
sfolder = src
ofolder = bin
flags = -lpthread -g

keywordSearch: main.o keyword.o
	${CC} ${ofolder}/main.o ${ofolder}/keyword.o ${ofolder}/output.o -o ${ofolder}/keywordSearch.out ${flags}
	./${ofolder}/keywordSearch.out testcases/testCase1.txt testcases/testCase2.txt

main.o:
	${CC} -c ${sfolder}/main.c -o ${ofolder}/main.o ${flags}

keyword.o:
	${CC} -c ${sfolder}/keyword.c -o ${ofolder}/keyword.o ${flags}
	${CC} -c ${sfolder}/output.c -o ${ofolder}/output.o ${flags}



clean:
	rm -f ./${ofolder}/*.out ./${ofolder}/*.o