target = TestApp.exe
src = $(wildcard *.c)
hfiles = $(wildcard *.h)
obj = $(src:.c=.o)

LDFLAGS =

$(target): $(obj) $(hfiles)
	gcc -o $@ $^ $(LDFLAGS)
	$(target)

$(obj): $(src)
	gcc -c $^
	
all: $(target)

run:
	TestApp.exe
	
.PHONY: clean
clean:
	rm -f $(obj) $(target)