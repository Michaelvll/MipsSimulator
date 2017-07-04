#include "PredictorClass.h"

bool PredictorClass::istaken()
{
	return counter[pattern].istaken();
}

void PredictorClass::new_pattern(bool taken)
{
	if (taken) --counter[pattern];
	else ++counter[pattern];
	pattern <<= 1;
	if (taken) {
		pattern |= 1;
	}
	pattern &= 0xF;
}