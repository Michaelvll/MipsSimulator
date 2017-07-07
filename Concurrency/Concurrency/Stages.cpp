#include "Cache.h"
#include "MipsSimulatorClass.h"
#include <condition_variable>
#include <mutex>
#include <thread>
#include "UsefulStructures.h"
#include "MipsSimulatorClass.h"
#include "Stages.h"

extern Cache cache;
extern Cache tmpcache;
extern MipsSimulatorClass MipsSimulator;
extern UsefulStructures usefulstructures;
Stages stage;

void Stages::Instruction_Fetch() {
	/// Fetch the instruction from the memory
	/// (in this simulator the instruction is stored in another container, but it
	/// can be assumed that it is in the memory)
	/// In this stage control hazard might take place for the memory can be read
	/// or write once in a same clock cycle

	if (!cache.IFdat.valid)
		return;
	Cache::IFdata data(cache.IFdat);
	Cache::IDdata ID;
	ID.valid = true;
	ID.PC = data.PC;
	// clog << "---\nInstruction Fetch for the instrcution at PC: " << myPC <<
	// endl;
	// MipsSimulator.log << "---\nInstruction Fetch for the instrcution at PC: "
	// << myPC << endl;

	ID.token = MipsSimulator.expr[ID.PC];
	MipsSimulator.PC = ID.PC + 1;
	ID.valid = true;
	// clog << "Fetch a instruction at PC: " << MipsSimulator.PC - 1 << token <<
	// endl;
	// MipsSimulator.log << "Fetch a instruction at PC: " << MipsSimulator.PC - 1
	// << '\n' << token << endl;

	tmpcache.IDdat.Change(ID);
}

void Stages::Data_Preparation() {
	/// Data preparation stage of the ins. on the pipeline
	/// In this stage data hazard might happened when the register, needed to be
	/// read has not finished writing process by the ins. before
	/// If a register needed to be read is in busy mode then pause the pipeline
	/// behind this ins.
	// clog << "---\nData Prepared for the instruction at PC: " << myPC << " whose
	// op is " << token.op << endl;
	// MipsSimulator.log << "---\nData Prepared for the instruction at PC: " <<
	// myPC << " whose op is " << token.op << endl;
	// clog << token << endl;
	// MipsSimulator.log << token << endl;
	if (!cache.IDdat.valid)
		return;
	Cache::IDdata data(cache.IDdat);
	UsefulStructures::Token token = data.token;
	long long r[5];

	MipsSimulator.op_class_tab[UsefulStructures::op_num::empty]->data_preparation(
		token, r);
	if (MipsSimulator.run_state == UsefulStructures::pip_run_state::run) {
		if (token.op >= UsefulStructures::op_num::add &&
			token.op <= UsefulStructures::op_num::sne) {
			if (token.op == UsefulStructures::op_num::mul2 ||
				token.op == UsefulStructures::op_num::mulu2 ||
				token.op == UsefulStructures::op_num::div2 ||
				token.op == UsefulStructures::op_num::div2) {
				usefulstructures.addBusy(UsefulStructures::reg_num::lo,MipsSimulator.busyreg);
				usefulstructures.addBusy(UsefulStructures::reg_num::hi,MipsSimulator.busyreg);
			}
			else {
				usefulstructures.addBusy(static_cast<int>(r[0]), MipsSimulator.busyreg);
			}
		}
		else if (token.op >= UsefulStructures::op_num::b &&
			token.op <= UsefulStructures::op_num::jr) {
			MipsSimulator.run_state = UsefulStructures::pip_run_state::jump;
			usefulstructures.addBusy(UsefulStructures::reg_num::pc, MipsSimulator.busyreg);
		}
		else if (token.op == UsefulStructures::op_num::jal ||
			token.op == UsefulStructures::op_num::jalr) {
			MipsSimulator.run_state = UsefulStructures::pip_run_state::jump;
			r[2] = 31;
			r[3] = data.PC + 1;
			usefulstructures.addBusy(UsefulStructures::reg_num::pc,MipsSimulator.busyreg);
			usefulstructures.addBusy(31, MipsSimulator.busyreg);
		}
		else if (token.op >= UsefulStructures::op_num::la &&
			token.op <= UsefulStructures::op_num::lw) {
			usefulstructures.addBusy(static_cast<int>(r[0]), MipsSimulator.busyreg);
		}
		else if (token.op >= UsefulStructures::op_num::move &&
			token.op <= UsefulStructures::op_num::mflo) {
			usefulstructures.addBusy(static_cast<int>(r[0]), MipsSimulator.busyreg);
		}
		else if (token.op == UsefulStructures::op_num::syscall) {
			if (r[1] == 5 || r[1] == 9) {
				usefulstructures.addBusy(static_cast<int>(r[0]), MipsSimulator.busyreg);
			}
			else if (r[1] == 10 || r[1] == 17) {
				MipsSimulator.run_state = UsefulStructures::pip_run_state::stopALL;
			}
		}
		else if (token.op == UsefulStructures::op_num::nop) {
			MipsSimulator.run_state = UsefulStructures::pip_run_state::wait;
		}
	}

	tmpcache.EXdat.Change(
		Cache::EXdata(cache.IDdat.PC, cache.IDdat.token.op, r, true));
}

void Stages::Execution() {
	/// Execution of the ins. on the pipeline
	/// In this stage the command will be fully recognized and the calculations
	/// will be done
	/// Register that will be written in is locked into busy mode
	// clog << "---\nExecution for the instruction at PC: " << myPC << " whose op
	// is " << token.op << endl;
	// MipsSimulator.log << "---\nExecution for the instruction at PC: " << myPC
	// << " whose op is " << token.op << endl;
	if (!cache.EXdat.valid) {
		tmpcache.MAdat.valid = false;
		return;
	}

	Cache::EXdata data(cache.EXdat);
	int op = data.op;
	long long r[5];
	for (int i = 0; i < 5; ++i) {
		r[i] = cache.EXdat.r[i];
	}
	bool ok = MipsSimulator.op_class_tab[op]->exec(r);
	if (ok) {
		// clog << "Get a common command and run" << endl;
		// MipsSimulator.log << "Get a common command and run" << endl;
	}
	else {
		if (r[4] == 0) {
			// clog << "Get a jump command and clear the instructions before this one"
			// << endl;
			// MipsSimulator.log << "Get a jump command and clear the instructions
			// before this one" << endl;
			r[1] = data.PC + 1;
		}
	}

	tmpcache.MAdat.Change(Cache::MAdata(data.PC, r, true));
}

void Stages::Memory_Access() {
	/// Memory Access stage of the ins. on pipeline
	/// Load/write the data from/to the RAM or the I/O devices
	/// In this stage might read or write the Ram which may cause the control
	/// hazard to the instruction fetch stage
	// clog << "---\nMemory Access for the instruction at PC: " << myPC << " whose
	// op is " << token.op << endl;
	// MipsSimulator.log << "---\nMemory Access for the instruction at PC: " <<
	// myPC << " whose op is " << token.op << endl;
	if (!cache.MAdat.valid)
		return;
	Cache::MAdata data(cache.MAdat);
	long long r[5];
	for (int i = 0; i < 5; ++i) {
		r[i] = data.r[i];
	}
	MipsSimulator.op_class_tab[UsefulStructures::op_num::empty]->memory_access(r);
	tmpcache.WBdat.Change(Cache::WBdata(data.PC, r, true));
}

void Stages::Write_Back() {
	/// Write back stage of the ins.on pipeline
	/// Write back the results of the stages before to certain registers(including
	/// PC register)
	/// The locked register will be released
	// MipsSimulator.log << "---\nWrite Back for the instruction at PC: " << myPC
	// << " whose op is " << token.op << endl;

	if (!cache.WBdat.valid)
		return;
	Cache::WBdata data(cache.WBdat);
	long long r[5];
	for (int i = 0; i < 5; ++i) {
		r[i] = data.r[i];
	}
	MipsSimulator.op_class_tab[UsefulStructures::op_num::empty]->write_back(r);
}