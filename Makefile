
CFLAGS := -O0 -g -Wall -Wextra -pedantic \
	-fstack-protector-strong \
	-fstack-protector-all \
	-fsanitize=shift \
	-fsanitize=undefined \
	-fsanitize=address \
	-fsanitize=alignment \
	-fsanitize=bool \
	-fsanitize=bounds \
	-fsanitize=bounds-strict \
	-fsanitize=enum \
	-fsanitize=float-cast-overflow \
	-fsanitize=float-divide-by-zero \
	-fsanitize=integer-divide-by-zero \
	-fsanitize=null \
	-fsanitize=object-size \
	-fno-sanitize-recover=all \
	-fsanitize=return \
	-fsanitize=returns-nonnull-attribute \
	-fsanitize=signed-integer-overflow

#CFLAGS := -O0 -g -Wall -Wextra -pedantic
CC := gcc

test: liblist.c liblist.h liblist_test.c
	$(CC) $(CFLAGS) -o $@ $(filter %.c,$^)

clean:
	rm -f *.o test
