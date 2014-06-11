include ../common/include.mk

main: main.c common/common.h cluster.o net.o logger.o
	${CC} main.c ${OBJECT_DIR}/cluster.o ${OBJECT_DIR}/net.o ${OBJECT_DIR}/logger.o ${CFLAGS} ${BUILD_DIR}/main ${EXTERNAL_LIBS}

cluster.o:
	${CC} cluster/cluster.c ${DO_NOT_LINK} ${CFLAGS} ${OBJECT_DIR}/cluster.o 

net.o:
	${CC} net/net.c ${DO_NOT_LINK} ${CFLAGS} ${OBJECT_DIR}/net.o 

logger.o:
	${CC} logger/logger.c ${DO_NOT_LINK} ${CFLAGS} ${OBJECT_DIR}/logger.o

all: main cluster net logger 

clean:
	${RECURSIVE_CLEAN_CMD} ${BUILD_DIR}/*;
	
cleanall:
	${RECURSIVE_CLEAN_CMD} ${BUILD_DIR}/* ${OBJECT_DIR}/*;

rebuildall: cleanall all
