DIR_L4_SRC ?= /home/puplauskas/code/l4re-base-20.08.0/src/l4
DIR_L4_BUILD ?= /home/puplauskas/code/l4re-base-20.08.0/obj/l4/amd64

PKGDIR ?= .
L4DIR ?= ${DIR_L4_SRC}
O = ${DIR_L4_BUILD}

TARGET = ipc2_server ipc2_client
SRC_CC_ipc2_server = server.cc
SRC_CC_ipc2_client = client.cc
REQUIRES_LIBS = libstdc++ libpthread
DEPENDS_PKGS  = $(REQUIRES_LIBS)

include $(L4DIR)/mk/prog.mk