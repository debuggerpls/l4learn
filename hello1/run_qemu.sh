#!/bin/bash

# somehow it doesnt use Makeconf.boot if building with diferent modules_list
# therefore, fiasco build path is required
make -C /home/deividas/projects/l4re-base-20.08.0/src/l4/builddir qemu E=hello1 MODULES_LIST=$PWD/modules.list MODULE_SEARCH_PATH=$PWD:/home/deividas/projects/l4re-base-20.08.0/src/fiasco/mybuild