target = Server.exe
src = $(wildcard *.c)\
		$(wildcard Server/*.c)\
		$(wildcard FileReadWrite/*.c)
hfiles = $(wildcard *.h)\
		$(wildcard Server/*.h)\
		$(wildcard FileReadWrite/*.h)
		
inc = -IServer -IFileReadWrite

obj = $(src:.c=.o)

cflags  = -Wall -lwsock32

$(target): $(obj) $(hfiles)
	@echo
	@echo 	'****************** Linking ******************'
	gcc  $^  $(cflags) -o $@

%.o:%.c
	@echo
	@echo 	'****************** Compiling $^ ******************'
	gcc $(cflags) $(inc) -c  -o $@ $<
	
	


	
all: clean $(target) 

.PHONY: run
run:
	@Server.exe
	
.PHONY: clean
clean:
	rm -f $(obj) $(target)