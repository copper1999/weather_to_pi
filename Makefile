CXX = g++
CXXFLAGS = -Wall -g -I/path/to/include -I/rapidjson -I/view -I/bcm2835
LDFLAGS = -lwiringPi -lst7735

SRCS = test.cpp 
OBJS = $(SRCS:.cpp=.o)


TARGET = build

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
