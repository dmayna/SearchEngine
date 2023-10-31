# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -g3 -lcurl 

# Source files
SRCS = ArgumentMap.cpp IndexBuilder.cpp InvertedIndex.cpp \
       SimpleIndex.cpp TextFileFinder.cpp WebCrawler.cpp \
       HtmlCleaner.cpp HtmlFetcher.cpp HttpsFetcher.cpp main.cpp

# Header files
HDRS = ArgumentMap.h IndexBuilder.h InvertedIndex.h SimpleIndex.h \
       TextFileFinder.h WebCrawler.h HtmlCleaner.h HtmlFetcher.h HttpsFetcher.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = SearchEngine

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(EXEC)
