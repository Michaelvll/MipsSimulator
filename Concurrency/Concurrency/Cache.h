#ifndef CACHE
#define CACHE
#include "UsefulStructures.h"
#include <iostream>
using std::ostream;
using std::endl;

class Cache {
public:
  void Change(const Cache &rc);
  void clear();
  friend ostream &operator<<(ostream &out, const Cache &da);

  class IFdata {
  public:
    bool valid = false;
    unsigned PC;
    IFdata() = default;
    IFdata(unsigned _PC, bool _vld);
    void Change(const IFdata &rd);
    friend ostream &operator<<(ostream &out, const IFdata &da);
  };
  class IDdata {
  public:
    bool valid = false;
    unsigned PC;
    UsefulStructures::Token token;
    IDdata() = default;
    IDdata(unsigned _PC, UsefulStructures::Token rt, bool _vld);
    void Change(const IDdata &rd);
    friend ostream &operator<<(ostream &out, const IDdata &da);
  };

  class EXdata {
  public:
    bool valid = false;
    unsigned PC;
    int op;
    long long r[5];

    EXdata() = default;
    EXdata(unsigned _PC, int op, long long rr[5], bool _vld);
    void Change(const EXdata &rd);
    friend ostream &operator<<(ostream &out, const EXdata &da);
  };

  class MAdata {
  public:
    bool valid = false;
    unsigned PC;
    long long r[5];

    MAdata() = default;
    MAdata(unsigned _PC, long long rr[5], bool _vld);
    void Change(const MAdata &rd);
    friend ostream &operator<<(ostream &out, const MAdata &da);
  };

  class WBdata {
  public:
    bool valid = false;
    unsigned PC;
    long long r[5];

    WBdata() = default;
    WBdata(unsigned _PC, long long rr[5], bool _vld);
    void Change(const WBdata &rdd);
    friend ostream &operator<<(ostream &out, const WBdata &da);
  };

  IFdata IFdat;
  IDdata IDdat;
  EXdata EXdat;
  MAdata MAdat;
  WBdata WBdat;
};

#endif // !CACHE
