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



	if (token.op == MipsSimulator.op_num_tab["mfhi"]) {
		r[1] = static_cast<long long>(MipsSimulator.reg[MipsSimulatorClass::op_num::mfhi]);
	}
	else if (token.op == MipsSimulator.op_num_tab["mflo"]) {
		r[1] = static_cast<long long> (MipsSimulator.reg[MipsSimulatorClass::op_num::mflo]);
	}
}

void PipelineClass::Memory_Access()
{
}

void PipelineClass::Write_Back()
{


	if (token.op == MipsSimulator.op_num_tab["jal"] || token.op == MipsSimulator.op_num_tab["jalr"]) {
		MipsSimulator.reg[31] = myPC;
	}
}

PipelineClass::PipelineClass(const unsigned & _PC):myPC(_PC){}

void PipelineClass::StartNext(UsefulStructures::pip_run_state state)
{

}
