# Makefile

src=imbue.c
obj=imbue.o
misc=Makefile
cflags=-Wall -g -O0 -Werror -pedantic -std=c11
target=imbue

all: $(target)

$(target) : $(obj) $(misc)
	gcc $(cflags) -o $(target) $(obj) $(lflags)

%.o : %.c $(misc) $(inc)
	gcc $(cflags) -c -o $@ $<

clean:
	rm -f $(obj) $(target)
