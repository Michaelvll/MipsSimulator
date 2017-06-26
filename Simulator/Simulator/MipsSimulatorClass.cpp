#include "MipsSimulatorClass.hpp"

MipsSimulatorClass::MipsSimulatorClass()
{
	reg_num_tab["zero"] = reg_num::zero;
	reg_num_tab["at"] = reg_num::at;
	reg_num_tab["v0"] = reg_num::v0;
	reg_num_tab["v1"] = reg_num::v1;
	reg_num_tab["a0"] = reg_num::a0;
	reg_num_tab["a1"] = reg_num::a1;
	reg_num_tab["a2"] = reg_num::a2;
	reg_num_tab["a3"] = reg_num::a3;
	reg_num_tab["t0"] = reg_num::t0;
	reg_num_tab["t1"] = reg_num::t1;
	reg_num_tab["t2"] = reg_num::t2;
	reg_num_tab["t3"] = reg_num::t3;
	reg_num_tab["t4"] = reg_num::t4;
	reg_num_tab["t5"] = reg_num::t5;
	reg_num_tab["t6"] = reg_num::t6;
	reg_num_tab["t7"] = reg_num::t7;
	reg_num_tab["s0"] = reg_num::s0;
	reg_num_tab["s1"] = reg_num::s1;
	reg_num_tab["s2"] = reg_num::s2;
	reg_num_tab["s3"] = reg_num::s3;
	reg_num_tab["s4"] = reg_num::s4;
	reg_num_tab["s5"] = reg_num::s5;
	reg_num_tab["s6"] = reg_num::s6;
	reg_num_tab["s7"] = reg_num::s7;
	reg_num_tab["t8"] = reg_num::t8;
	reg_num_tab["t9"] = reg_num::t9;
	reg_num_tab["k0"] = reg_num::k0;
	reg_num_tab["k1"] = reg_num::k1;
	reg_num_tab["gp"] = reg_num::gp;
	reg_num_tab["sp"] = reg_num::sp;
	reg_num_tab["s8"] = reg_num::s8;
	reg_num_tab["fp"] = reg_num::fp;
	reg_num_tab["ra"] = reg_num::ra;
}

void MipsSimulatorClass::readcode(std::istream & codein)
{
}
