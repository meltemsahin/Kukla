
/*
    @last change: 8 Nov '16

    Puppet from <Meltem Sahin>
    Copyright (C) 2016  
    Written by A. Arif Balik <arifbalik@outlook.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define LED_GROUP1 5
#define LED_GROUP2 6
#define SENSOR 8 // IR Sensor
#define MOTOR 9

#define INCREASE 1
#define DECREASE 0

void setup() {
  pinMode(LED_GROUP1, OUTPUT);
  pinMode(LED_GROUP2, OUTPUT);
  pinMode(SENSOR,INPUT);

}
int readSensor(){
  // for noise problem, we should ignore first detect and wait almost 30ms 
  if(digitalRead(SENSOR)) delay(30);
  
  return digitalRead(SENSOR);
}

int anm = INCREASE;
void fadeLed(int again){

  while(--again){
    for (int fadeValue = (anm == INCREASE) ? 0 : 70 ; fadeValue <= (anm == INCREASE) ? 70 : 0; fadeValue = (anm == INCREASE) ? fadeValue + 2 : fadeValue - 2 ) {
          analogWrite(LED_GROUP1, fadeValue);
          analogWrite(LED_GROUP2, (anm == INCREASE) ? map(fadeValue,0,70,40,0) : map(fadeValue,70,0,0,40));
          // wait for 200 milliseconds to see the dimming effect
          delay(200);
         }
     anm = !anm;
  }
}

void loop() {
  if(readSensor()){
    analogWrite(MOTOR, 70); 
    fadeLed(11); // 11 times ~= 2 minutes
  }
  else analogWrite(MOTOR, 0);
}
