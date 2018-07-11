//ar_lightning - Lightning detector
// based on 
// https://github.com/klauscam/Arduino-Lightning-Detector/


#define FASTADC 1
#define DELTIME 150
#define SENSITIVITY 0.3
#define POSOFFSET 2
#define NEGOFFSET 2




// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


int reading; // storing readings
int count; // count lighnings
int initial; // initial value 

void setup() {
#if FASTADC
 // set prescale to 16
 sbi(ADCSRA,ADPS2) ;
 cbi(ADCSRA,ADPS1) ;
 cbi(ADCSRA,ADPS0) ;
#endif
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(A4,INPUT);
  
  count=0;

      initial = (analogRead(A4)); // throw it away, it's garbage
      delay(1000); // wait for it to clarify

  initial = (analogRead(A4));
Serial.println("Initial: "+ String(initial));

}


void loop() {
  // put your main code here, to run repeatedly:
  reading = (analogRead(A4));
  if(reading > initial + POSOFFSET || reading < initial -  NEGOFFSET ) {
    count++;
    Serial.println("Hit: "+ String(count) + " " + String(reading) + " " + String(initial));
    delay(DELTIME);
  }
      initial = ((float)(initial)*(1.0-SENSITIVITY) + (float)(reading)*(1.0 + SENSITIVITY )) /2; // basically a low-pass filter

}


