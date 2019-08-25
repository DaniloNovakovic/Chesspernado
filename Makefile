CFLAGS = -Wall -std=c99

SRC=$(wildcard */*.c)

chesspernado: $(SRC)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)
	@echo "Output file: $@"