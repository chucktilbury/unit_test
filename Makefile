
-include unit_test.mak

all: $(TARGET)

$(TARGET): $(LIBRARY)
	make -C tests $(TARGET)

$(LIBRARY):
	make -C unit_test $(LIBRARY)

clean:
	make -C tests clean
	make -C unit_test clean
	rm -rf $(TARGET) $(LIBRARY)

format:
	make -C tests format
	make -C unit_test format
	make -C code format
