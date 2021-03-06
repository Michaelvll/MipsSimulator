#include "PipelineClass.h"
#include <iostream>
using std::endl;
using std::cout;
using std::clog;

extern MipsSimulatorClass MipsSimulator;
extern UsefulStructures usefulstructures;

void PipelineClass::Instruction_Fetch()
{
	/// Fetch the instruction from the memory 
	/// (in this simulator the instruction is stored in another container, but it can be assumed that it is in the memory)
	/// In this level control hazard might take place for the memory can be read or write once in a same clock cycle
	//clog << "---\nInstruction Fetch for the instrcution at PC: " << myPC << endl;
	//MipsSimulator.log << "---\nInstruction Fetch for the instrcution at PC: " << myPC << endl;
	myPC = MipsSimulator.PC;

	if (MipsSimulator.PC >= MipsSimulator.expr.size()) return;
	token = MipsSimulator.expr[MipsSimulator.PC++];
	op = token.op;
	
	//clog << "Fetch a instruction at PC: " << MipsSimulator.PC - 1 << token << endl;
	//MipsSimulator.log << "Fetch a instruction at PC: " << MipsSimulator.PC - 1 << '\n' << token << endl;

}

void PipelineClass::Data_Preparation(int &state, int busyreg[4])
{
	/// Data preparation level of the product on the pipeline
	/// In this level data hazard might happened when the register, needed to be read has not finished writing process by the instructions before 
	/// If a register needed to be read is in busy mode then pause the pipeline in front of this command
	//clog << "---\nData Prepared for the instruction at PC: " << myPC << " whose op is " << token.op << endl;
	//MipsSimulator.log << "---\nData Prepared for the instruction at PC: " << myPC << " whose op is " << token.op << endl;
	//clog << token << endl;
	//MipsSimulator.log << token << endl;

	MipsSimulator.op_class_tab[UsefulStructures::op_num::empty]->data_preparation(token, r, state, busyreg);
}

void PipelineClass::Execution(int &state, int busyreg[4])
{
	/// Execution of the products on the pipeline
	/// In this level the command will be fully recognized and the calculations will be done
	/// Register that will be written in is locked into busy mode
	//clog << "---\nExecution for the instruction at PC: " << myPC << " whose op is " << token.op << endl;
	//MipsSimulator.log << "---\nExecution for the instruction at PC: " << myPC << " whose op is " << token.op << endl;

	bool ok = MipsSimulator.op_class_tab[op]->exec(r, busyreg);
	if (ok) {
		//clog << "Get a common command and run" << endl;
		//MipsSimulator.log << "Get a common command and run" << endl;

		state = UsefulStructures::pip_run_state::run;
		return;
	}
	else {
		if (r[4] == 1) {
			//clog << "Get a jump command and clear the instructions before this one" << endl;
			//MipsSimulator.log << "Get a jump command and clear the instructions before this one" << endl;

			state = UsefulStructures::pip_run_state::clear;
		}
		else if (r[4] == 5) {
			//clog << "Get a nop command and pause for 5 cycle" << endl;
			//MipsSimulator.log << "Get a nop command and pause for 5 cycle" << endl;

			state = UsefulStructures::pip_run_state::pause;
		}
		else if (r[4] == -1) {
			//clog << "Get a syscall that stop the program" << endl;
			//MipsSimulator.log << "Get a syscall that stop the program" << endl;

			state = UsefulStructures::pip_run_state::stopALL;
		}
		else if (r[4] == -2) {
			//clog << "Get a syscall the stop the program and output a number" << endl;
			//MipsSimulator.log << "Get a syscall the stop the program and output a number" << endl;

			state = UsefulStructures::pip_run_state::stopALL;
			//cout << r[2] << endl;
		}
	}
	if (token.op == UsefulStructures::op_num::jal || token.op == UsefulStructures::op_num::jalr) {
		r[2] = 31;
		r[3] = myPC + 1;
		r[4] = 2;
		usefulstructures.addBusy(31, busyreg);
	}
}

void PipelineClass::Memory_Access(bool &memory_busy)
{
	/// Memory Access stage of the product on pipeline
	/// In this level might read or write the Ram which may cause the control hazard to the instruction fetch level
	//clog << "---\nMemory Access for the instruction at PC: " << myPC << " whose op is " << token.op << endl;
	//MipsSimulator.log << "---\nMemory Access for the instruction at PC: " << myPC << " whose op is " << token.op << endl;

	MipsSimulator.op_class_tab[UsefulStructures::op_num::empty]->memory_access(r, s, memory_busy);
}

void PipelineClass::Write_Back(int busyreg[4])
{
	/// Write back stage of the product on pipeline
	/// In this level the result of the stage befor will write back into certain registers, and it will release these registers into free mode
	//clog << "---\nWrite Back for the instruction at PC: " << myPC << " whose op is " << token.op << endl;
	//MipsSimulator.log << "---\nWrite Back for the instruction at PC: " << myPC << " whose op is " << token.op << endl;

	MipsSimulator.op_class_tab[UsefulStructures::op_num::empty]->write_back(r, busyreg, s);
}

PipelineClass::PipelineClass(const unsigned & _PC) :myPC(_PC) {}

void PipelineClass::StartNext(int &state,bool &memory_busy, int &wait, int busyreg[4])
{
	/// Start the next level of the product on the pipeline
	//clog << "\nStart next level of the instruction on PC: " << myPC;
	//MipsSimulator.log << "\nStart next level of the instruction on PC: " << myPC;

	if (state == UsefulStructures::pip_run_state::run) {
		
	//clog << " (Run)" << endl;
	//MipsSimulator.log << " (Run)" << endl;

		switch (nowpip) {
		case 1:
			if (memory_busy) {
				break;
			}
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
			Memory_Access(memory_busy);
			++nowpip;
			break;
		case 5:
			Write_Back(busyreg);
			++nowpip;
			break;
		}
	}
	else if (state == UsefulStructures::pip_run_state::pause) {
		//clog << " (Pause)" << endl;
		//MipsSimulator.log << " (Pause)" << endl;

	}
	else if (state == UsefulStructures::pip_run_state::clear) {
		//clog << " It's in clear state" << endl;
		//MipsSimulator.log << " It's in clear state" << endl;

		switch (nowpip) {
		case 4:
			Memory_Access(memory_busy);
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
