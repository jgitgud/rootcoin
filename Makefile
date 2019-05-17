# ---- Configuration options ----

# External/implicit variables:
# - CXX: The C++ compiler, such as g++ or clang++.
# - CXXFLAGS: Any extra user-specified compiler flags (can be blank).
# - AR: The archiver, such as ar.
# Mandatory compiler flags
CXX_FLAGS=-fsanitize=undefined       

# Optimization level
CXX_FLAGS += -O1

# ---- Targets to build ----
#CRYPTO_LIB=$(shell pwd)/cryptolib
CRYPTO_LIB=./cryptolib
CRYPTO_LIB_FILE=bitcoincrypto
LIB_PATH=$(CRYPTO_LIB)/$(CRYPTO_LIB_FILE)

all: test.cpp $(CRYTPO_LIB_FILE)
	g++ $(CXX_FLAGS) test.cpp -o test.out -I$(CRYPTO_LIB) -L$(CRYPTO_LIB) -l$(CRYPTO_LIB_FILE) 

test: TransactionDemo.cpp Transaction.cpp Utils.cpp $(CRYTPO_LIB_FILE)
	g++ $(CXX_FLAGS) TransactionDemo.cpp Transaction.cpp Utils.cpp -o TransactionDemo.out -I$(CRYPTO_LIB) -L$(CRYPTO_LIB) -l$(CRYPTO_LIB_FILE) 