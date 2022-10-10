CC = gcc
sfolder = src
ofolder = bin
flags = -lcunit -g
objs = Main_testdriver.o valid.o valid_suite.o result.o result_suite.o

Main_testdriver.c : $(objs)
	${CC} bin/Main_testdriver.o bin/valid.o bin/valid_suite.o bin/result.o bin/result_suite.o -o bin/file.tests ${flags}
	./bin/file.tests

Main_testdriver.o: src/Main_testdriver.c
	${CC} -c src/Main_testdriver.c -o bin/Main_testdriver.o

valid.o: src/valid.c
	${CC} -c src/valid.c -o bin/valid.o

valid_suite.o: src/valid_suite.c
	${CC} -c src/valid_suite.c -o bin/valid_suite.o

result.o: src/result.c
	${CC} -c src/result.c -o bin/result.o

result_suite.o: src/result_suite.c
	${CC} -c src/result_suite.c -o bin/result_suite.o

clean: 
	echo "Cleaning files ..."
	rm -f bin/file.tests bin/Main_testdriver.o bin/valid.o bin/valid_suite.o bin/result.o bin/result_suite.o
