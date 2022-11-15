CXX = g++

CXXFLAG = -Wall -std=c++11 -O2 -lpthread  -lmysqlclient

TARGET = test

OBJS1 = main.cpp

OBJS2 = Restaurant.cpp

OBJS3 = Customer.cpp

OBJS4 = Transaction.cpp

OBJS5 = Response.cpp

OBJS6 = Socket.cpp

$(TARGET) : $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6)
		$(CXX) -o $@ $(CXXFLAG) $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6)

clean:
		rm $(TARGET)