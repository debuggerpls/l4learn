DIR_L4_SRC ?= /home/puplauskas/code/l4re-base-20.08.0/src/l4
DIR_L4_BUILD ?= /home/puplauskas/code/l4re-base-20.08.0/obj/l4/amd64

PKGDIR ?= .
L4DIR ?= ${DIR_L4_SRC}
O = ${DIR_L4_BUILD}

TARGET = ipc0_server ipc0_client
SRC_CC_ipc0_server = server.cc
SRC_CC_ipc0_client = client.cc

include $(L4DIR)/mk/prog.mk