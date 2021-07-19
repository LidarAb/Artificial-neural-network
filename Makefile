CC=g++
CXXFLAGS= -Wall -Wvla -Wextra -Werror -g -std=c++17
LDFLAGS= -lm
HEADERS= Matrix.h Activation.h Dense.h MlpNetwork.h Digit.h
OBJS= Matrix.o Activation.o Dense.o MlpNetwork.o 

%.o : %.c

test_network.o: test_network.cpp
	$(CC) $(LDFLAGS) -c test_network.cpp

test_network: test_network.o $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

mlpnetwork: $(OBJS) main.o
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJS) : $(HEADERS)

.PHONY: clean test
clean:
	rm -rf *.exe
	rm -rf *.o
	rm -rf mlpnetwork




