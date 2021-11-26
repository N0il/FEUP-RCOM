SDIR=./src
IDIR=./includes
ODIR=./out
CC=gcc

IFLAGS    =-I$(IDIR)
CFLAGS=-g -Wall

TRANSMITTER_O_FILES=$(ODIR)/transmitter.o
RECEIVER_O_FILES   =$(ODIR)/receiver.o

O_FILES=$(ODIR)/alarme.o $(ODIR)/api_receiver.o $(ODIR)/api_transmitter.o $(ODIR)/api.o $(ODIR)/buffer_utils.o $(ODIR)/byte_stuffing.o $(ODIR)/file.o 

all: transmitter receiver

transmitter: $(TRANSMITTER_O_FILES) $(O_FILES)
	$(CC) $^ -o $@

receiver: $(RECEIVER_O_FILES) $(O_FILES)
	$(CC) $^ -o $@

$(ODIR):
	mkdir -p $(ODIR)

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean: 
	rm -f transmitter receiver
	rm -rf $(ODIR)


# all: transmitter receiver

# transmitter: app/transmitter/transmitter.c api/api.c
# 		gcc -Wall app/transmitter/transmitter.c -o t 
# # api/api.c api/api_transmitter/api_transmitter.c alarm/alarme.c -o t

# receiver: app/receiver/receiver.c api/api.h api/api_receiver/api_receiver.h
# 		gcc -Wall app/receiver/receiver.c -o e
# # api/api.c api/api_receiver/api_receiver.c alarm/alarme.c -o e

# clean:
# 		rm -f t

# # app/transmitter/transmitter.h api/api.h api/api_transmitter/api_transmitter.h alarm/alarme.h

# # app/receiver/receiver.h api/api.h api/api_receiver/api_receiver.h alarm/alarme.h