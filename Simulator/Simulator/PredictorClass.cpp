#include "PredictorClass.h"

void PredictorClass::pattern_taken()
{
	++counter[pattern];
}

void PredictorClass::pattern_untaken()
{
	--counter[pattern];
}

bool PredictorClass::istaken()
{
	return counter[pattern].istaken();
}

void PredictorClass::new_pattern(bool taken)
{
	pattern = pattern << 1;
	if (taken) {
		pattern |= 1;
	}
	pattern = ((pattern << 4) >> 4);
}