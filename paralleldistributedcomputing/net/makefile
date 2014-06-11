include ../../common/include.mk

RELATIVE_OBJECT_DIR = ../${OBJECT_DIR}

net.o: net.c net.h
	${CC} net.c ${DO_NOT_LINK} ${CFLAGS} ${RELATIVE_OBJECT_DIR}/net.o

clean:
	${CLEAN_CMD} ${RELATIVE_OBJECT_DIR}/net.o
