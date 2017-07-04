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
	/// In this stage control hazard might take place for the memory can be read or write once in a same clock cycle
	myPC = MipsSimulator.PC;
	//clog << ---\nInstruction Fetch for the instrcution at PC: " << myPC << endl;
	//MipsSimulator.log << "---\nInstruction Fetch for the instrcution at PC: " << myPC << endl;

	if (MipsSimulator.PC >= MipsSimulator.expr.size()) return;
	token = MipsSimulator.expr[MipsSimulator.PC++];
	op = token.op;

	//clog << Fetch a instruction at PC: " << MipsSimulator.PC - 1 << token << endl;
	//MipsSimulator.log << "Fetch a instruction at PC: " << MipsSimulator.PC - 1 << '\n' << token << endl;

}

void PipelineClass::Data_Preparation(int &state, int busyreg[4])
{
	/// Data preparation stage of the ins. on the pipeline
	/// In this stage data hazard might happened when the register, needed to be read has not finished writing process by the ins. before 
	/// If a register needed to be read is in busy mode then pause the pipeline behind this ins.
	//clog << ---\nData Prepared for the instruction at PC: " << myPC << " whose op is " << token.op << endl;
	//MipsSimulator.log << "---\nData Prepared for the instruction at PC: " << myPC << " whose op is " << token.op << endl;
	//clogtoken << endl;
	//MipsSimulator.log << token << endl;
	if (token.op >= 27 && token.op <= 38) {
		//tmp

		// Get the last 4 bits for hash
		hash_myPC = myPC & 0xF;
		//clog << Get the hash of myPC: " << static_cast<int>(hash_myPC) << endl;
		//MipsSimulator.log << "Get the hash of myPC: " << hash_myPC << endl;

		if (MipsSimulator.predict_tab[hash_myPC].istaken()) {
			state = UsefulStructures::pip_run_state::predict_taken;
			//clog << Predict that it would take the jump!" << endl;
			//MipsSimulator.log << "Predict that it would take the jump!" << endl;
		}
		else {
			//clog << Predict that it would not take the jump!" << endl;
			//MipsSimulator.log << "Predict that it would not take the jump!" << endl;
		}
	}

	// In the next function the state can change to the pause again
	MipsSimulator.op_class_tab[UsefulStructures::op_num::empty]->data_preparation(token, r, state, busyreg);
	if (state == UsefulStructures::pip_run_state::predict_taken) {
		if (token.op >= 27 && token.op <= 32) {
			MipsSimulator.PC = static_cast<unsigned>(r[2]);
			//clog << Change the PC to: " << r[2] << endl;
			//MipsSimulator.log << "Change the PC to: " << r[2] << endl;
		}
		else {
			MipsSimulator.PC = static_cast<unsigned> (r[1]);
			//clog << Change the PC to: " << r[1] << endl;
			//MipsSimulator.log << "Change the PC to: " << r[1] << endl;
		}
	}
	
}

void PipelineClass::Execution(int &state, int busyreg[4])
{
	/// Execution of the ins. on the pipeline
	/// In this stage the command will be fully recognized and the calculations will be done
	/// Register that will be written in is locked into busy mode
	//clog <<"---\nExecution for the instruction at PC: " << myPC << " whose op is " << token.op << endl;
	//MipsSimulator.log << "---\nExecution for the instruction at PC: " << myPC << " whose op is " << token.op << endl;
	
	//tmp
	if (token.op >= 27 && token.op <= 38) {
		MipsSimulator.condition_jump_num++;
	}
	
		bool ok = MipsSimulator.op_class_tab[op]->exec(r, busyreg);
	if (ok) {
		//clog << "Get a common command and run" << endl;
		//MipsSimulator.log << "Get a common command and run" << endl;

		state = UsefulStructures::pip_run_state::run;
		return;
	}
	else {
		if (r[4] == 0) {
			MipsSimulator.predict_tab[hash_myPC].new_pattern(false);
			if (state == UsefulStructures::pip_run_state::predict_taken) {
				// The prediction is wrong
				state = UsefulStructures::pip_run_state::clear;
				r[1] = myPC + 1;
				//clog << The prediction get wrong, clear the instructions before this one and change plan to change the PC back to: " << r[1] << endl;
				//MipsSimulator.log << "The prediction get wrong, clear the instructions before this one and change plan to change the PC back to: " << r[1] << endl;
			}
			else {
				//tmp
				MipsSimulator.correct_predict++;

				// The prediction is correct
				state = UsefulStructures::pip_run_state::run;
				r[1] = -1;
				//clog << The prediction get right and coninue running" << endl;
				//MipsSimulator.log << "The prediction get right and coninue running" << endl;
			}
		}
		else if (r[4] == 1) {
			//clog << Get a jump command and clear the instructions before this one" << endl;
			//MipsSimulator.log << "Get a jump command and clear the instructions before this one" << endl;
			MipsSimulator.predict_tab[hash_myPC].new_pattern(true);
			if (state == UsefulStructures::pip_run_state::predict_taken) {
				//tmp
				MipsSimulator.correct_predict++;

				// The prediction is correct
				state = UsefulStructures::pip_run_state::run;
				r[1] = -1;
				usefulstructures.delBusy(static_cast<int>(r[0]), busyreg);
				//clog << The prediction get right and continue running" << endl;
				//MipsSimulator.log << "The prediction get right and continue running" << endl;
			}
			else {
				// The prediction is wrong
				state = UsefulStructures::pip_run_state::clear;
				//clog << The prediction get wrong" << endl;
				//MipsSimulator.log << "The prediction get wrong and clear the instruction behind" << endl;
			}
		}
		else if (r[4] == 4) {
			//clog << Get a jump command and clear the instructions before this one" << endl;
			//MipsSimulator.log << "Get a jump command and clear the instructions before this one" << endl;
			state = UsefulStructures::pip_run_state::clear;
		}
		else if (r[4] == 5) {
			//clog << Get a nop command and pause for 5 cycle" << endl;
			//MipsSimulator.log << "Get a nop command and pause for 5 cycle" << endl;

			state = UsefulStructures::pip_run_state::pause;
		}
		else if (r[4] == -1) {
			//clog << Get a syscall that stop the program" << endl;
			//MipsSimulator.log << "Get a syscall that stop the program" << endl;

			state = UsefulStructures::pip_run_state::stopALL;
		}
		else if (r[4] == -2) {
			//clog << Get a syscall the stop the program and output a number" << endl;
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

void PipelineClass::Memory_Access()
{
	/// Memory Access stage of the ins. on pipeline
	/// Load/write the data from/to the RAM or the I/O devices 
	/// In this stage might read or write the Ram which may cause the control hazard to the instruction fetch stage
	//clog << ---\nMemory Access for the instruction at PC: " << myPC << " whose op is " << token.op << endl;
	//MipsSimulator.log << "---\nMemory Access for the instruction at PC: " << myPC << " whose op is " << token.op << endl;

	MipsSimulator.op_class_tab[UsefulStructures::op_num::empty]->memory_access(r);
}

void PipelineClass::Write_Back(int busyreg[4])
{
	/// Write back stage of the ins.on pipeline
	/// Write back the results of the stages before to certain registers(including PC register)
	/// The locked register will be released
	//MipsSimulator.log << "---\nWrite Back for the instruction at PC: " << myPC << " whose op is " << token.op << endl;

	MipsSimulator.op_class_tab[UsefulStructures::op_num::empty]->write_back(r, busyreg);
}

PipelineClass::PipelineClass() {}

void PipelineClass::StartNext(int &state, int &wait, int busyreg[4])
{
	/// Start the next stage of the ins. on the pipeline
	//clog << \nStart next stage of the instruction on PC: " << myPC;
	//MipsSimulator.log << "\nStart next stage of the instruction";

	if (state == UsefulStructures::pip_run_state::run || state == UsefulStructures::pip_run_state::predict_taken) {

		//clog <<  (Run)" << endl;
		//MipsSimulator.log << " (Run)" << endl;

		switch (nowpip) {
		case 1:
			Instruction_Fetch();
			++nowpip;
			break;
		case 2:
			Data_Preparation(state, busyreg);
			if (state == UsefulStructures::pip_run_state::run || state == UsefulStructures::pip_run_state::predict_taken) ++nowpip;
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
		//clog <<  (Pause)" << endl;
		//MipsSimulator.log << " (Pause)" << endl;

	}
	else if (state == UsefulStructures::pip_run_state::clear) {
		//clog <<  It's in clear state" << endl;
		//MipsSimulator.log << " It's in clear state" << endl;

		switch (nowpip) {
		case 3:
			Execution(state, busyreg);
			if (state == UsefulStructures::pip_run_state::pause) wait = 5;
			++nowpip;
			break;
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
