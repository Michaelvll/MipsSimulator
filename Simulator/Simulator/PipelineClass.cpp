#include "PipelineClass.h"
#include <iostream>
using std::endl;
using std::cout;

extern MipsSimulatorClass MipsSimulator;

void PipelineClass::Instruction_Fetch()
{
	if (MipsSimulator.PC >= MipsSimulator.expr.size()) return;
	token = MipsSimulator.expr[MipsSimulator.PC++];
	argutoken = token;
	op = token.op;
	MipsSimulator.log << "Fetch a instruction at PC: " << MipsSimulator.PC - 1 << token << endl;
}

void PipelineClass::Data_Preparation(int &state, int busyreg[4])
{
	MipsSimulator.op_class_tab[UsefulStructures::op_num::empty]->data_preparation(argutoken, r, state, busyreg);
}

void PipelineClass::Execution(int &state, int busyreg[4])
{
	bool ok = MipsSimulator.op_class_tab[op]->exec(r, busyreg);
	if (ok) {
		state = UsefulStructures::pip_run_state::run;
		return;
	}
	else {
		if (r[4] == 1) {
			state = UsefulStructures::pip_run_state::clear;
		}
		else if (r[4] == 5) {
			state = UsefulStructures::pip_run_state::pause;
		}
		else if (r[4] == -1) {
			state = UsefulStructures::pip_run_state::stopALL;
		}
		else if (r[4] == -2) {
			state = UsefulStructures::pip_run_state::stopALL;
			cout << r[2] << endl;
		}
	}
}

void PipelineClass::Memory_Access()
{
	MipsSimulator.op_class_tab[UsefulStructures::op_num::empty]->memory_access(r, s);
}

void PipelineClass::Write_Back(int busyreg[4])
{
	MipsSimulator.op_class_tab[UsefulStructures::op_num::empty]->write_back(r, busyreg, s);
}

PipelineClass::PipelineClass(const unsigned & _PC) :myPC(_PC) {}

void PipelineClass::StartNext(int &state, int &wait, int busyreg[4])
{
	if (mywait > 0) {
		--mywait;
		return;
	}
	if (state == UsefulStructures::pip_run_state::run) {
		switch (nowpip) {
		case 1:
			Instruction_Fetch();
			break;
		case 2:
			Data_Preparation(state, busyreg);
			break;
		case 3:
			Execution(state, busyreg);
			if (state == UsefulStructures::pip_run_state::pause) wait = 5;
			break;
		case 4:
			Memory_Access();
			break;
		case 5:
			Write_Back(busyreg);
			break;
		}
		++nowpip;
	}
	else if (state == UsefulStructures::pip_run_state::pause) {
		mywait = 1;
	}
	else if (state == UsefulStructures::pip_run_state::clear) {
		switch (nowpip) {
		case 4:
			Memory_Access();
			break;
		case 5:
			Write_Back(busyreg);
			break;
		}
		++nowpip;
	}
	else {
		//state == stopALL
		return;
	}
}
