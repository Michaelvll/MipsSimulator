#include "PipelineClass.h"
#include <iostream>
using std::endl;
using std::cout;
using std::clog;

extern MipsSimulatorClass MipsSimulator;

void PipelineClass::Instruction_Fetch()
{
	clog << "---\nInstruction Fetch for the instrcution at PC: " << myPC << endl;
	if (MipsSimulator.PC >= MipsSimulator.expr.size()) return;
	token = MipsSimulator.expr[MipsSimulator.PC++];
	argutoken = token;
	op = token.op;
	//MipsSimulator.log << "Fetch a instruction at PC: " << MipsSimulator.PC - 1 << token << endl;
	clog << "Fetch a instruction at PC: " << MipsSimulator.PC - 1 << token << endl;
}

void PipelineClass::Data_Preparation(int &state, int busyreg[4])
{
	//MipsSimulator.log << "Data Prepared for the instruction at PC: " << myPC << endl;
	clog << "---\nData Prepared for the instruction at PC: " << myPC << " whose op is " << token.op << endl;
	//MipsSimulator.log << "argutoken is " << argutoken << endl;
	clog << "arguToken is " << argutoken << endl;
	MipsSimulator.op_class_tab[UsefulStructures::op_num::empty]->data_preparation(argutoken, r, state, busyreg);
}

void PipelineClass::Execution(int &state, int busyreg[4])
{
	clog << "---\nExecution for the instruction at PC: " << myPC << " whose op is " << token.op << endl;
	bool ok = MipsSimulator.op_class_tab[op]->exec(r, busyreg);
	if (ok) {
		clog << "Get a common command and run" << endl;
		state = UsefulStructures::pip_run_state::run;
		return;
	}
	else {
		if (r[4] == 1) {
			clog << "Get a jump command and clear the instructions before this one" << endl;
			state = UsefulStructures::pip_run_state::clear;
		}
		else if (r[4] == 5) {
			clog << "Get a nop command and pause for 5 cycle" << endl;
			state = UsefulStructures::pip_run_state::pause;
		}
		else if (r[4] == -1) {
			clog << "Get a syscall that stop the program" << endl;
			state = UsefulStructures::pip_run_state::stopALL;
		}
		else if (r[4] == -2) {
			clog << "Get a syscall the stop the program and output a number" << endl;
			state = UsefulStructures::pip_run_state::stopALL;
			cout << r[2] << endl;
		}
	}
}

void PipelineClass::Memory_Access()
{
	clog << "---\nMemory Access for the instruction at PC: " << myPC << " whose op is " << token.op << endl;
	MipsSimulator.op_class_tab[UsefulStructures::op_num::empty]->memory_access(r, s);
}

void PipelineClass::Write_Back(int busyreg[4])
{
	clog << "---\nWrite Back for the instruction at PC: " << myPC << " whose op is " << token.op << endl;
	MipsSimulator.op_class_tab[UsefulStructures::op_num::empty]->write_back(r, busyreg, s);
}

PipelineClass::PipelineClass(const unsigned & _PC) :myPC(_PC) {}

void PipelineClass::StartNext(int &state, int &wait, int busyreg[4])
{
	////MipsSimulator.log << "Start next level of the instruction on PC: " << myPC;
	clog << "Start next level of the instruction on PC: " << myPC;

	if (state == UsefulStructures::pip_run_state::run) {
		//MipsSimulator.log << " Run" << endl;
	clog << " Run" << endl;
		switch (nowpip) {
		case 1:
			Instruction_Fetch();
			++nowpip;
			break;
		case 2:
			Data_Preparation(state, busyreg);
			if (state == UsefulStructures::pip_run_state::run) ++nowpip;
			break;
		case 3:
			Execution(state, busyreg);
			if (state == UsefulStructures::pip_run_state::pause) wait = 5;
			++nowpip;
			break;
		case 4:
			Memory_Access();
			++nowpip;
			break;
		case 5:
			Write_Back(busyreg);
			++nowpip;
			break;
		}
	}
	else if (state == UsefulStructures::pip_run_state::pause) {
		clog << " Pause" << endl;
	}
	else if (state == UsefulStructures::pip_run_state::clear) {
		clog << " It's in clear state" << endl;
		switch (nowpip) {
		case 4:
			Memory_Access();
			break;
		case 5:
			Write_Back(busyreg);
			state = UsefulStructures::pip_run_state::run;
			break;
		}
		++nowpip;
	}
	else {
		//state == stopALL
		return;
	}
}
