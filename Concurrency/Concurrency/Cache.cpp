#include "Cache.h"

Cache cache;
Cache tmpcache;

Cache::IFdata::IFdata(unsigned _PC, bool _vld) : valid(_vld), PC(_PC) {}

void Cache::IFdata::Change(const IFdata &rd) {
  PC = rd.PC;
  valid = rd.valid;
}

Cache::IDdata::IDdata(unsigned _PC, UsefulStructures::Token rt, bool _vld) {
  PC = _PC;
  token = rt;
  valid = _vld;
}

void Cache::IDdata::Change(const IDdata &rd) {
  PC = rd.PC;
  token = rd.token;
  valid = rd.valid;
}

Cache::EXdata::EXdata(unsigned _PC, int _op, long long rr[5], bool _vld)
    : valid(_vld), PC(_PC) {
  op = _op;
  for (int i = 0; i < 5; ++i) {
    r[i] = rr[i];
  }
}

void Cache::EXdata::Change(const EXdata &rd) {
  PC = rd.PC;
  op = rd.op;
  for (int i = 0; i < 5; ++i) {
    r[i] = rd.r[i];
  }
  valid = rd.valid;
}

Cache::MAdata::MAdata(unsigned _PC, long long rr[5], bool _vld)
    : valid(_vld), PC(_PC) {
  for (int i = 0; i < 5; ++i) {
    r[i] = rr[i];
  }
}

void Cache::MAdata::Change(const MAdata &rd) {
  PC = rd.PC;
  for (int i = 0; i < 5; ++i) {
    r[i] = rd.r[i];
  }
  valid = rd.valid;
}

Cache::WBdata::WBdata(unsigned _PC, long long rr[5], bool _vld)
    : valid(_vld), PC(_PC) {
  for (int i = 0; i < 5; ++i) {
    r[i] = rr[i];
  }
}

void Cache::WBdata::Change(const WBdata &rd) {
  PC = rd.PC;
  for (int i = 0; i < 5; ++i) {
    r[i] = rd.r[i];
  }
  valid = rd.valid;
}

void Cache::Change(const Cache &rc) {
  IFdat.valid = false;
  IDdat.Change(rc.IDdat);
  EXdat.Change(rc.EXdat);
  MAdat.Change(rc.MAdat);
  WBdat.Change(rc.WBdat);
}

void Cache::clear() {
  IFdat.valid = IDdat.valid = EXdat.valid = MAdat.valid = WBdat.valid = false;
}

ostream &operator<<(ostream &out, const Cache &da) {
  out << "The Cache is " << endl;
  out << da.IFdat << "---\n"
      << da.IDdat << "---\n"
      << da.EXdat << "---\n"
      << da.MAdat << "---\n"
      << da.WBdat << endl;
  return out;
}

ostream &operator<<(ostream &out, const Cache::IFdata &da) {
  out << "IFdata: "
      << "[ valid: " << da.valid << ", PC: " << da.PC << " ]" << endl;
  return out;
}

ostream &operator<<(ostream &out, const Cache::IDdata &da) {
  out << "IDdata: [ valid: " << da.valid << ", PC: " << da.PC
      << ", \ntoken: " << da.token << " ]" << endl;
  return out;
}

ostream &operator<<(ostream &out, const Cache::EXdata &da) {
  out << "EXdata: [ valid: " << da.valid << ", PC: " << da.PC
      << ", op: " << da.op << ", r: [ " << da.r[0] << ' ' << da.r[1] << ' '
      << da.r[2] << ' ' << da.r[3] << ' ' << da.r[4] << " ]" << endl;
  return out;
}

ostream &operator<<(ostream &out, const Cache::MAdata &da) {
  out << "MAdata: [ valid: " << da.valid << ", PC: " << da.PC << ", r: [ "
      << da.r[0] << ' ' << da.r[1] << ' ' << da.r[2] << ' ' << da.r[3] << ' '
      << da.r[4] << " ]" << endl;
  return out;
}

ostream &operator<<(ostream &out, const Cache::WBdata &da) {
  out << "WBdata: [ valid: " << da.valid << ", PC: " << da.PC << ", r: [ "
      << da.r[0] << ' ' << da.r[1] << ' ' << da.r[2] << ' ' << da.r[3] << ' '
      << da.r[4] << " ]" << endl;
  return out;
}
