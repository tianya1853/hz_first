TGT = demo

CC  = gcc
AR  = ar cr
CFLAGS  += -Wall -lrt



SRCS =*.c
OBJS =$(SRCS:%.c=%.obj)


RM = -rm -rf
#RM = -rm


all:module
	
module:$(SRCS)
	$(CC) -o $(TGT)  $(SRCS) $(CFLAGS)
clean:
	$(RM) $(TGT) 
