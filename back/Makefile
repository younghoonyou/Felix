CXX = g++

CXXFLAG = -Wall -std=c++11 -O2 -lmysqlclient

TARGET = test

OBJS1 = main.cpp

OBJS2 = ./source/Restaurant.cpp

OBJS3 = ./source/Customer.cpp

OBJS4 = ./source/Transaction.cpp

OBJS5 = ./source/Response.cpp

OBJS6 = ./source/Socket.cpp

$(TARGET) : $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6)
		$(CXX) -o $@ $(CXXFLAG) $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6)

clean:
		rm $(TARGET)