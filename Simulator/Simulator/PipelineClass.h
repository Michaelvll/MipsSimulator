#ifndef PIPELINECLASS
#define PIPELINECLASS
#include "MipsSimulatorClass.h"
#include "UsefulStructures.h"
#include "CommandClass.h"
#include <string>
using std::string;

extern MipsSimulatorClass MipsSimulator;

class PipelineClass {
private:
	UsefulStructures::Token token; // for IF
	UsefulStructures::arguToken argutoken;
	int op = 0;
	long long r[5] = { 0 };
	unsigned myPC = 0;
	int hash_myPC;

	//int mywait = 0;

	void Instruction_Fetch();
	void Data_Preparation(int &state,int busyreg[4]);
	void Execution(int &state, int busyreg[4]);
	void Memory_Access();
	void Write_Back(int busyreg[4]);
public:
	// Here should be some useful varient
	int nowpip = 1;
	PipelineClass();

	void StartNext(int &state, int &wait, int busyreg[4]);

};

#endif //PIPELINECLASS