LINK_FLGS = -c -g
COMPILER = gcc
OBJECT_DIR = ../build/obj

cluster.o: cluster.c cluster.h
	$(COMPILER) $(LINK_FLGS) cluster.c -o ${OBJECT_DIR}/cluster.o

clean:
	rm ${OBJECT_DIR}/cluster.o
