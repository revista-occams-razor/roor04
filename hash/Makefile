all:roorsum simple

simple:simple.c
	${CC} -Wall -o $@ $< -lssl -lcrypto

roorsum:roorsum.c
	${CC} -Wall -o $@ $< -lssl -lcrypto


.PHONY:
clean:
	rm -f roorsum simple
