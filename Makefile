TARGETS = libmatrix.a
SRCS = mat.cc program.cc
OBJS = $(SRCS:.cc=.o)
CXXFLAGS = -Wall -Werror -pedantic -O3

default: $(TARGETS)

mat.o : mat.cc mat.h
program.o: program.o program.h

libmatrix.a : mat.o mat.h stack.h vec.h program.o program.h
	$(AR) -r $@  $(OBJS)

clean :
	$(RM) $(OBJS) $(TARGETS)
