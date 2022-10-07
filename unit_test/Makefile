
-include ../unit_test.mak

OBJS	=	memory.o \
		ptr_lists.o \
		asserts.o \
		unit_tests.o \
		mocks.o \
		stubs.o \
		tests.o \
		sections.o

all: $(LIBRARY)

%.o: %.c
	gcc -Wpedantic -g -c -o $@ $<

$(LIBRARY): $(OBJS)
	ar -crs $@ $(OBJS)

clean:
	rm -f $(OBJS) $(LIBRARY)

format:
	clang-format -i *.c *.h
