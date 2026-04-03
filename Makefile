TEST_TARGET = rsa_test
TEST_NONCE = nonce_test

CXX = g++
CXXFLAGS = -Wall -Wextra -O3 -std=c++17

INCLUDES = -Iutils
NINCLUDES = -Inet/handshake

LDFLAGS = -lssl -lcrypto

SRC = utils/RSA.cpp test/gen_rsa_test.cpp
NONCE = net/handshake/nonce.cpp test/nonce_gen_test.cpp

all:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(TEST_TARGET) $(LDFLAGS)

clean:
	rm -f $(TEST_TARGET)

run: all
	./$(TEST_TARGET)

nonce: 
	$(CXX) $(CXXFLAGS) $(NINCLUDES) $(NONCE) -o $(TEST_NONCE) $(LDFLAGS)

nonce_run: nonce
	./$(TEST_NONCE)

.PHONY: all clean run nonce nonce_run
