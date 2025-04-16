# Copyright (C) 2023 Gramine contributors
# SPDX-License-Identifier: BSD-3-Clause

CFLAGS = -Wall -Wextra
LDFLAGS = -lrt -lpthread


ifeq ($(DEBUG),1)
GRAMINE_LOG_LEVEL = debug
CFLAGS += -g
else
GRAMINE_LOG_LEVEL = error
CFLAGS += -O3
endif

.PHONY: all
all: vector_add vector_add.manifest
ifeq ($(SGX),1)
all: vector_add.manifest.sgx vector_add.sig
endif

vector_add: vector_add.o



vector_add.o: vector_add.c

vector_add.manifest: vector_add.manifest.template vector_add
	gramine-manifest \
		-Dlog_level=$(GRAMINE_LOG_LEVEL) \
		$< $@
	gramine-manifest-check $@

vector_add.sig vector_add.manifest.sgx &: vector_add.manifest
	gramine-sgx-sign \
		--manifest $< \
		--output $<.sgx
	gramine-manifest-check $<.sgx

ifeq ($(SGX),)
GRAMINE = gramine-direct
else
GRAMINE = gramine-sgx
endif


.PHONY: clean
clean:
	$(RM) *.sig *.manifest.sgx *.manifest *.o vector_add OUTPUT 

.PHONY: distclean
distclean: clean
