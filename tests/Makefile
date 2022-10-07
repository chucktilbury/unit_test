
-include ../unit_test.mak

OBJS	=	test_main.o

all: $(TARGET)

%.o: %.c
	gcc -Wpedantic -I$(PROJ_DIR)/unit_test -I$(PROJ_DIR)/code -g -c -o $@ $<

$(TARGET): $(LIBRARY) $(OBJS)
	gcc -g -o $@ $(OBJS) -L$(PROJ_DIR) -lut

clean:
	rm -f $(OBJS) $(TARGET)

format:
	clang-format -i *.c *.h
