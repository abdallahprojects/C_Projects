#gcc = C:\MinGW\bin\gcc.exe
target = Server.exe
src = $(wildcard *.c)\
		$(wildcard NET/*.c)\
		$(wildcard fileH/*.c)
dirs = $(dir $(src))

hfiles := $(foreach dir,$(dirs),$(wildcard $(dir)/*.h))

inc = $(foreach dir,$(dirs),$(addprefix -I,$(dir)))

obj = $(src:.c=.o)

cflags  = -Wall -lwsock32
version:
	make --version
gcc_version:
	gcc --version
	
$(target): $(obj) 
	@echo
	@echo 	'****************** Linking ******************'
	gcc  $^  $(cflags) -o $@

%.o:%.c
	@echo
	@echo 	'****************** Compiling $^ ******************'
	gcc $(cflags) $(inc) -c  -o $@ $<
	
	


	
all: clean gcc_version version $(target) 

.PHONY: run
run:
	@$(target)
	
.PHONY: clean
clean:
	rm -f $(obj) $(target)