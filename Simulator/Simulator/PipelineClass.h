#ifndef PIPELINECLASS
#define PIPELINECLASS
#include "MipsSimulatorClass.h"
#include "UsefulStructures.h"
#include "CommandClass.h"

extern MipsSimulatorClass MipsSimulator;

class PipelineClass {
private:
	unsigned myPC;
	UsefulStructures::Token token;
	long long r[4];

	void Instruction_Fetch();
	void Data_Preparation();
	void Execution();
	void Memory_Access();
	void Write_Back();
public:
	// Here should be some useful varient
	int nowpip = 1;
	PipelineClass(const unsigned & _PC);

	void StartNext(UsefulStructures::pip_run_state state);

};

#endif //PIPELINECLASS