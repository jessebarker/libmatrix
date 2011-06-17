TARGETS = libmatrix.a
TESTS = matrix_inverse_test
SRCS = mat.cc program.cc matrix_inverse_test.cc
OBJS = $(SRCS:.cc=.o)
CXXFLAGS = -Wall -Werror -pedantic -O3

# Make sure to build both the library targets and the tests, and generate 
# a make failure if the tests don't pass.
default: $(TARGETS) $(TESTS) run_tests

# Main library targets here.
mat.o : mat.cc mat.h
program.o: program.cc program.h
libmatrix.a : mat.o mat.h stack.h vec.h program.o program.h
	$(AR) -r $@  $(OBJS)

# Tests and execution targets here.
matrix_inverse_test.o: matrix_inverse_test.cc mat.h
matrix_inverse_test: matrix_inverse_test.o libmatrix.a
	$(CXX) -o $@ $?
run_tests: $(TESTS)
	./matrix_inverse_test
clean :
	$(RM) $(OBJS) $(TARGETS)
