TARGETS = libmatrix.a
SRCS = mat.cc
OBJS = $(SRCS:.cc=.o)
CXXFLAGS = -Wall -Werror -pedantic -O3

default: $(TARGETS)

mat.o : mat.cc mat.h

libmatrix.a : mat.o mat.h stack.h vec.h
	$(AR) -r $@  $(OBJS)

clean :
	$(RM) $(OBJS) $(TARGETS)
