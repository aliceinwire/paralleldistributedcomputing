include ../../common/include.mk

sorttester: sorttester.c testclient
	${CC} sorttester.c ${CFLAGS} sorttester

testclient: testclient.c
	${CC} testclient.c ${CFLAGS} testclient

clean:
	${CLEAN_CMD} sorttester
	${CLEAN_CMD} testclient
