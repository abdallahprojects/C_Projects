target = Client.exe
src = $(wildcard *.c)\
		$(wildcard Client/*.c)\
		$(wildcard FileRead/*.c)
hfiles = $(wildcard *.h)\
		$(wildcard Client*.h)\
		$(wildcard FileRead/*.h)
		
inc = -IClient -IFileRead

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
	@Client.exe
	
.PHONY: clean
clean:
	rm -f $(obj) $(target)