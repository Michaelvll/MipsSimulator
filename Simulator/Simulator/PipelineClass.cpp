#include "PipelineClass.h"
using std::endl;

extern MipsSimulatorClass MipsSimulator;

void PipelineClass::Instruction_Fetch()
{
	token = MipsSimulator.expr[MipsSimulator.PC++];
	MipsSimulator.log << "Fetch a instruction at PC: " << MipsSimulator.PC-1 << token << endl;
}

void PipelineClass::Data_Preparation()
{

}

void PipelineClass::Execution()
{
}

void PipelineClass::Memory_Access()
{
}

void PipelineClass::Write_Back()
{
}

void PipelineClass::StartNext(MipsSimulatorClass::pip_run_state state)
{

}
