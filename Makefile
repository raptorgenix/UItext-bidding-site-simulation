CXX = g++
CXXFLAGS	= -std=c++17 -Wall

all: bidToBuy

clean:
	rm bidToBuy Store.o Product.o TextUI.o Seller.o Buyer.o User.o

bidToBuy: main.cpp Store.o Product.o TextUI.o Seller.o Buyer.o User.o
	$(CXX) $(CXXFLAGS) main.cpp Store.o Product.o TextUI.o Seller.o Buyer.o User.o -o bidToBuy

TextUI.o: TextUI.cpp
	$(CXX) $(CXXFLAGS) -c TextUI.cpp

Store.o: Store.cpp
	$(CXX) $(CXXFLAGS) -c Store.cpp

User.o: User.cpp
	$(CXX) $(CXXFLAGS) -c User.cpp

Product.o: Product.cpp
	$(CXX) $(CXXFLAGS) -c Product.cpp

Seller.o: Seller.cpp
	$(CXX) $(CXXFLAGS) -c Seller.cpp

Buyer.o: Buyer.cpp
	$(CXX) $(CXXFLAGS) -c Buyer.cpp