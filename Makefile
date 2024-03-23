CXX      ?= g++
CXXFLAGS ?= -std=c++20
LINK.o := $(LINK.cc) 

CPPFLAGS += -O3 -Wall -I. -I../pacs-examples/Examples/include
LDLIBS += -L../pacs-examples/Examples/lib -Wl,-rpath=../pacs-examples/Examples/lib -lpacs


# get all files *.cpp
SRCS = $(wildcard *.cpp)
# get the corresponding object filecd 
OBJS = $(SRCS:.cpp=.o)
# get all headers in the working directory
HEADERS = $(wildcard *.hpp)

exe_sources = $(filter main%.cpp,$(SRCS))
EXEC = $(exe_sources:.cpp=)



.PHONY = all clean distclean

.DEFAULT_GOAL = all

all: $(EXEC)

$(EXEC): $(OBJS)

$(OBJS): $(SRCS) 

clean:
	$(RM) -f $(EXEC) $(OBJS)

distclean:
	$(MAKE) clean
	$(RM) -f ./doc $(DEPEND)
	$(RM) *.out *.bak *~