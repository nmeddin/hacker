#######################################################################
#
# Copyright (C) 2018 David C. Harrison. All right reserved.
#
# You may not use, distribute, publish, or modify this code without 
# the express written permission of the copyright holder.
#
#######################################################################

CFLAGS = -Wall -Isrc -lpthread -lcrypt -g
CC = g++ -std=c++17

all: hacker server

hacker: src/hacker.cc crack.o
	$(CC) -o $@ $^ $(CFLAGS)

server: src/server.cc crack.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	@rm hacker server

submit: clean 
	@tar czvf ~/CMPS109-Lab9.tar.gz \
	    src/*.cc src/*.h 
