include ../build_config.mk

OBJS = proc_kv.o serv.o 
LIBS = ./net/libnet.a ./util/libutil.a 
EXES = ssdb-server


all: ${OBJS} ssdb-server.o
	make -C net
	make -C util
	make -C client
	${CXX} -o ${EXES} ssdb-server.o ${OBJS} ${LIBS} ${CLIBS} client/SSDB_impl.o

ssdb-server.o: ssdb-server.cpp
	${CXX} ${CFLAGS} -c ssdb-server.cpp

proc_kv.o: serv.h processors/proc_kv.cpp
	${CXX} ${CFLAGS} -c processors/proc_kv.cpp

serv.o: serv.h serv.cpp
	${CXX} ${CFLAGS} -c serv.cpp

clean:
	rm -f ${EXES} *.o *.exe *.a
	make clean -C net
	make clean -C util
	make clean -C client
