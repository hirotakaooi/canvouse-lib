#ifndef Canvouse_h
#define Canvouse_h

#include "Arduino.h"

class Canvouse
{
public:
  Canvouse();
  void init(int _In1, int _In2, int _Me1, int _Me2);
  void G2B(int t, float von);
  void B2G(int t, float voff);
  void Gkeep(int t, float vonk);
  void Bkeep(int t, float voffk);
  
private:
  int In1;
  int In2;
  int Me1;
  int Me2;
  int ct;
  int tlim = 10;
  float* va= new float[tlim];
  int vp;
  int vn;
  float val;  
};

#endif

