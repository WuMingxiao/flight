CC=gcc
CFLAGS =-Wall -g 

INCLUDE += -I src/

LIB_OPT= -lcurses -lpthread 

dirs:= src/
SRC := $(foreach dir,$(dirs),$(wildcard $(dir)*.c))
OBJ := $(foreach dir,$(dirs),$(wildcard $(dir)*.o))
HD  := $(foreach dir,$(dirs),$(wildcard $(dir)*.h))

PROJ=flight

$(PROJ):$(patsubst %.c, %.o, $(SRC))  
	$(CC) $(CFLAGS)  -o $@ $^  $(LIB_OPT) 
	
%.o:%.c $(HD)
	$(CC) $(CFLAGS) $(INCLUDE)  -c -o $@ $< 

clean:
	rm $(OBJ) $(PROJ)

