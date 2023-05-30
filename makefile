CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic
LDFLAGS = -pthread

pipeline_st: pipeline_st.cpp isPrime.hpp ThreadSafeQueue.hpp ActiveObject.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f pipeline_st