TEST_TARGET = rsa_test

CXX = g++
CXXFLAGS = -Wall -Wextra -O3 -std=c++17

INCLUDES = -Iutils

LDFLAGS = -lssl -lcrypto

SRC = utils/RSA.cpp test/gen_rsa_test.cpp

all:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(TEST_TARGET) $(LDFLAGS)

clean:
	rm -f $(TEST_TARGET)

run: all
	./$(TEST_TARGET)

.PHONY: all clean run
