target = TestApp.exe
src = $(wildcard *.c)\
		$(wildcard Printer/*.c)
hfiles = $(wildcard *.h)\
		 $(wildcard Printer/*.h)
inc = Printer 
obj = $(src:.c=.o)
cflags = -Wall

$(target): $(obj) $(hfiles)
	@echo
	@echo 	'****************** Linking ******************'
	gcc $(cflags) -o $@ $^ 

%.o:%.c
	@echo
	@echo 	'****************** Compiling $^ ******************'
	gcc $(cflags) -I$(inc) -c  -o $@ $<
	
	


	
all: clean $(target) run

.PHONY: run
run:
	@TestApp.exe
	
.PHONY: clean
clean:
	rm -f $(obj) $(target)