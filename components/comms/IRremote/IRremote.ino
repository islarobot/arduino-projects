
#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()

{

Serial.begin(9600);
irrecv.enableIRIn(); //start the receiver


}

void loop()

{
if (irrecv.decode(&results))

  {
    Serial.println(results.value, HEX);
    irrecv.resume(); //receive next value
  }
}
