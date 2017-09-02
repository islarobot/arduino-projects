int analogPin = 5; / / level sensor connected to an analog port
int led = 13; / / Piranha LED connected to digital port 12
int val = 0; / / define a variable val initial value of 0
int data = 0; / / define a variable data initial value of 0
void setup ()
{
pinMode (led, OUTPUT); / / define led to an output pin
Serial.begin (9600); / / set the baud rate to 9600
}
void loop ()
{
val = analogRead (analogPin); / / read the analog value to the variable val
if (val> 700) {/ / determine whether more than 700 variables val
digitalWrite (led, HIGH); when / / variable val is greater than 700 , Piranha LED lights
}
else {
digitalWrite (led, LOW); when / / variable val is less than 700 , the lamp goes out piranha
}
data = val; / / variable is assigned to the variable data val
Serial.println (data); / / Serial print variable data
delay (100);
}
