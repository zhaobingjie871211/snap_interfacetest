#
# Copyright 2016, 2017 International Business Machines
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

ifndef SNAP_ROOT
ifneq ("$(wildcard ../../ActionTypes.md)","")
SNAP_ROOT=$(abspath ../../)
else
$(info You probably have defined a wrong $$SNAP_ROOT.)
$(error Please make sure that $$SNAP_ROOT is set up correctly.)
endif
endif

include ../config.mk

libversion = $(VERSION)

CFLAGS += -fPIC -fno-strict-aliasing
LDLIBS += -lcxl -lpthread

ifdef BUILD_SIMCODE
CFLAGS += -D_SIM_
LDFLAGS += -L$(PSLSE_ROOT)/libcxl -Wl,-rpath,$(PSLSE_ROOT)/libcxl
LIBS += $(PSLSE_ROOT)/libcxl/libcxl.so
endif

libnameA = libsnap
projA = $(libnameA).a \
	$(libnameA).so \
	$(libnameA).so.$(MAJOR_VERSION) \
	$(libnameA).so.$(libversion)

srcA = snap.c
objsA = $(srcA:.c=.o)

projs += $(projA)

all: $(projs)

ifdef BUILD_SIMCODE
$(projs): $(PSLSE_ROOT)/libcxl/libcxl.so

$(PSLSE_ROOT)/libcxl/libcxl.so:
	$(MAKE) -C `dirname $@`
endif

### libA
__$(libnameA).o: $(objsA)
	$(LD) $(XLDFLAGS) -r -o $@ $^

$(libnameA).a: __$(libnameA).o
	$(AR) rcs $@ $^

$(libnameA).so:  $(libnameA).so.$(libversion)
	ln -sf $< $@

$(libnameA).so.$(MAJOR_VERSION): $(libnameA).so.$(libversion)
	ln -sf $< $@
# SONAMEA=-Wl,-soname,$(libnameA).so.$(MAJOR_VERSION)

$(libnameA).so.$(libversion): __$(libnameA).o
	$(CC) $(LDFLAGS) -shared  $(SONAMEA) \
		 -o $@ $^ $(libsA) $(LDLIBS)

install: all
	mkdir -p $(LIB_INSTALL_PATH)
	cp -auv $(projA) $(LIB_INSTALL_PATH)

# general things
%.o: %.c
	$(CC) -c $(CPPFLAGS) $($(@:.o=)_CPPFLAGS) $(CFLAGS) $< -o $@
	$(CC) -MM $(CPPFLAGS) $($(@:.o=)_CPPFLAGS) $(CFLAGS) $< > $*.d

clean distclean:
	$(RM) *.o *.d $(projs) *.so *.so.* *~

-include $(objsA:.o=.d) $(objsB:.o=.d)
