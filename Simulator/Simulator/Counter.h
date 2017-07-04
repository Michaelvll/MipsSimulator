#ifndef COUNTER
#define COUNTER
#include <bitset>
using std::bitset;

class Counter {
	bitset<2> c;
	// c belongs to a set {0,1,2,3}
	// 0: strongly taken
	// 1: weakly taken
	// 2: weakly untaken
	// 3: strongly untaken
public:
	Counter();
	Counter& operator++();
	Counter& operator--();
	bool istaken();
};

#endif // COUNTER
