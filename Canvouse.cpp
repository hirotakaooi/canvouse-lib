#include "Arduino.h"
#include "Canvouse.h"

Canvouse::Canvouse()
{

}

void Canvouse::init(int _In1, int _In2, int _Me1, int _Me2){
  In1 = _In1;
  In2 = _In2;
  Me1 = _Me1;
  Me2 = _Me2;
  pinMode(_In1, OUTPUT);
  pinMode(_In2, OUTPUT);
  ct=0;
  tlim = 10;
  float* va = new float[tlim+1];
  for(int i =0; i < tlim+1; i++){
    va[i] = 0;
  }
  vp = 0;
  vn = 0;
  val = 0;  
}

void Canvouse::G2B(int t, float von)
{

  int cnt = 0;
  float ave = 0;
  digitalWrite(In1, 1);
  digitalWrite(In2, 0);
  
  for(int i; i < t; i++){
    vp = analogRead(Me1);
    vn = analogRead(Me2);
    val = 5*((float)vp-(float)vn)/1024;
    Serial.print(cnt);
    Serial.print(":");
    Serial.print(val);
    Serial.println();


    va[i%tlim] = val;
    ave = 0;
    for(int m = 0; m < tlim; m++){
      ave += va[m];
    }
    ave = ave/tlim;
    if(abs(ave-val) < 0.01){
      break;
    }
    

    if(val < von){
      digitalWrite(In1, 1);
      digitalWrite(In2, 0);
      delay(1000);
    }else if(val - va[(i-1)%tlim] > 0.01){
      Serial.print(val - va[(i-1)%tlim]);
      digitalWrite(In1, 1);
      digitalWrite(In2, 0);
      delay(1000);      
    }else{
      break;
      }
    
    cnt = cnt +1;        
  }
  digitalWrite(In1, 0);
  digitalWrite(In2, 0);
  ct = cnt+10;    
}

void Canvouse::B2G(int t, float voff){
  int cnt = 0;
  digitalWrite(In1, 0);
  digitalWrite(In2,1);
  for(int i = 0; i < ct; i++){
    vp = analogRead(Me1);
    vn = analogRead(Me2);
    val = 5*((float)vp-(float)vn)/1024;
    Serial.print(cnt);
    Serial.print(":");
    Serial.print(val);
    Serial.println(); 
    cnt++;
    delay(1000);    
  }
    
  for(int i = cnt; i < t-ct; i++){
    vp = analogRead(Me1);
    vn = analogRead(Me2);
    val = 5*((float)vp-(float)vn)/1024;
    Serial.print(cnt);
    Serial.print(":");
    Serial.print(val);
    Serial.println(); 
    cnt++;
    if(val>voff){
      digitalWrite(In1, 0);
      digitalWrite(In2, 1);
      delay(1000);
    }else{
      break;
    }
  }
  digitalWrite(In1, 0);
  digitalWrite(In2, 0);
  for(int m = 0; m < tlim; m++){
    va[m] = 0;
  }

}

void Canvouse::Bkeep(int t, float vonk){
  for (int i=0; i < t; i++){
    vp = analogRead(Me1);
    vn = analogRead(Me2);
    val = 5*((float)vp-(float)vn)/1024;
    Serial.print(val);
    Serial.println();
    if (val < vonk){
      digitalWrite(In1, 1);
      digitalWrite(In2, 0);
      delay(1000);
    }else{
      digitalWrite(In1, 0);
      digitalWrite(In2, 0);
      delay(1000);
    }        
  }
}

void Canvouse::Gkeep(int t, float voffk){
  for (int i=0; i < t; i++){
    vp = analogRead(Me1);
    vn = analogRead(Me2);
    val = 5*((float)vp-(float)vn)/1024;
    Serial.print(val);
    Serial.println();
    if (val > voffk){
      digitalWrite(In1, 0);
      digitalWrite(In2, 1);
      delay(1000);
    }else{
      digitalWrite(In1, 0);
      digitalWrite(In2, 0);
      delay(1000);
    }        
  }
}




