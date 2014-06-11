include ../../common/include.mk

RELATIVE_OBJECT_DIR = ../${OBJECT_DIR}

logger.o: logger.c logger.h
	${CC} logger.c ${DO_NOT_LINK} ${CFLAGS} ${RELATIVE_OBJECT_DIR}/logger.o

clean:
	${CLEAN_CMD} ${RELATIVE_OBJECT_DIR}/logger.o
