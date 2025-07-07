String incomingByte;
bool Ok = false;
void setup()
{
  Serial.begin(115200);
  // put your setup code here, to run once:

}

void loop()
{
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    incomingByte = Serial.readString();
    if (incomingByte == "ST0G")
    {
      //Serial.println("Starting transmition");
      Ok =true;
      delay(1000);
    }
    else if(incomingByte == "ST1G")
    {
      Ok=false;
      //Serial.println("Transmition Terminated");
      delay(1000);
    }
  }
  if(Ok)
    {
      Serial.print((String)"3" + "A" + "307" + "B" + "500" + "C" + "\n");
      delay(2000);
      Serial.print((String)"128" + "A" + "85" + "B" + "500" + "C" + "\n");
      delay(2000);
      Serial.print((String)"417" + "A" + "0" + "B" + "500" + "C" + "\n");
      delay(2000);
      Serial.print((String)"722" + "A" + "85" + "B" + "500" + "C" + "\n");
      delay(2000);
    }
}
