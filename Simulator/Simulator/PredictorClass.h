#ifndef PREDICTORCLASS
#define PREDICTORCLASS
#include "Counter.h"

class PredictorClass {
private:
	Counter counter[16];
	// counter belongs to a set {0,1,2,3}
	// 0: strongly taken
	// 1: weakly taken
	// 2: weakly untaken
	// 3: strongly untaken
	char pattern;

public:
	bool istaken();
	void new_pattern(bool taken);
};


#endif // PREDICTORCLASS
