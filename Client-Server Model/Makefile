target = S&C_APP
src = 	$(wildcard Application/*.c)\
		$(wildcard Basic_Software_Layer/*.c)
		
hfiles = $(wildcard Basic_Software_Layer/*.h)
inc = Basic_Software_Layer 
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
	
	


	
all: $(target).exe


clean: rm -f $(obj) $(target)