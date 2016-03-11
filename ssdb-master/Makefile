PREFIX=/usr/local/ssdb

$(shell sh build.sh 1>&2)
include build_config.mk

all:
	make -C deps/jemalloc-3.3.1/
	mkdir -p var
	make -C src

clean:
	make -C src clean
	rm -rf var
clean_all:
	make -C src clean
	rm -rf var
	make -C deps/jemalloc-3.3.1/ clean
	
