bool LED_STATE1 = true;
bool LED_STATE2 = true;

void setup() {
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  cli();                      //stop interrupts for till we make the settings 

  //Timer2 (interrupt each 1.024ms)
  // interrupt time = 1/(16Mhz/1024) * 16 =  1.024ms.
  TCCR2A = 0;                 // Reset entire TCCR1A to 0 
  TCCR2B = 0;                 // Reset entire TCCR1B to 0
  TCCR2B |= B00000111;        //Set CS20, CS21 and CS22 to 1 so we get prescalar 1024  
  TIMSK2 |= B00000100;        //Set OCIE1B to 1 so we enable compare match B
  OCR2B = 16;                //Finally we set compare register B to this value 
  sei();                      //Enable back the interrupts
}

void loop() {
  // put your main code here, to run repeatedly:
}


//With the settings above, this IRS will trigger each 1.024ms.
ISR(TIMER2_COMPB_vect){  
  TCNT2=0;                             
  LED_STATE1 = !LED_STATE1;    //Invert LED state
  digitalWrite(5,LED_STATE1);  //Write new state to the LED on pin D5
}
