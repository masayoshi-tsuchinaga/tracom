#include "Adafruit_MPR121_sample_ide.h"		// Additional Header

#define DST_ADDR		0x4088
#define DST_PANID		0xABCD
bool button[6];

void setup() {
	  // put your setup code here, to run once:
	int i;
	SubGHz.init();
	for(i=3;i<=8;i++)
	{
		pinMode(i,INPUT_PULLUP);
		button[i-3] = true;
	}
	SubGHz.begin(36,0xABCD,100,20);
	pinMode(26,OUTPUT);
}
char payload[100];
void loop() {
  // put your main code here, to run repeatedly:
  int i;
  bool txflag;
  txflag = false;

  Print.init(payload,sizeof(payload));
  
  for(i=3;i<=8;i++) {
  	char data = digitalRead(i);
  	Print.p( (data == 1) ? "0,":"1,");
  	if(data != button[i-3]) {
	  	txflag = true;
  		button[i-3] = data;
  	}
  }
  Print.ln();
  digitalWrite(26,LOW);
  if(txflag) SubGHz.send(DST_PANID,DST_ADDR,payload,Print.len(),NULL);
  digitalWrite(26,HIGH);
  
   sleep(100);
}
