CXX=g++
CXXFLAGS=-g -std=c++11 -Wall

all : mycloud_server mcput mcget mcdel mclist

mycloud_server : ServerMain.cpp server.cpp
	$(CXX) $(CXXFLAGS) -o mycloud_server ServerMain.cpp server.cpp

mcput : mcput.cpp StoreClient.cpp BaseClient.cpp
	$(CXX) $(CXXFLAGS) -o mcput mcput.cpp StoreClient.cpp BaseClient.cpp

mcget : mcget.cpp GetClient.cpp BaseClient.cpp
	$(CXX) $(CXXFLAGS) -o mcget mcget.cpp GetClient.cpp BaseClient.cpp
	 
mcdel : mcdel.cpp DelClient.cpp BaseClient.cpp
	$(CXX) $(CXXFLAGS) -o mcdel mcdel.cpp DelClient.cpp BaseClient.cpp
	 
mclist : mclist.cpp ListClient.cpp BaseClient.cpp
	$(CXX) $(CXXFLAGS) -o mclist mclist.cpp ListClient.cpp BaseClient.cpp
	 
clean:
	-rm -f *.o *.a
	-rm -f $(all)
