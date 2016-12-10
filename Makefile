# Makefile
# CS 2200 PRJ5 - Fall 2016

src=file_stream.c
obj=file_stream.o
misc=Makefile
cflags=-Wall -g -O0 -Werror -pedantic -std=c11
target=stenography

all: $(target)

$(target) : $(obj) $(misc)
	gcc $(cflags) -o $(target) $(obj) $(lflags)

%.o : %.c $(misc) $(inc)
	gcc $(cflags) -c -o $@ $<

clean:
	rm -f $(obj) $(target)

submit: clean
	tar zcvf prj5-submit.tar.gz $(inc) $(src) $(misc) answers.txt
