#include<EEPROM.h>


// setting physical pins for board to read
int xpin = A2, zpin = A1, pres = A4, temp = A5;  
int Xaccel, Zaccel;
String Data, XaccelString, ZaccelString, Pressure, Temp;

//setting parameter for data collection
int Xhigh = 100; // Setting an arbitrary high point in z and x axes in
int Zhigh = 100; // which accelerometer determines when to take data (NEEDS TO BE TESTED FOR CORRECT LIMITS)
int sensormin = 0; //minimum sensor value when read from analogRead...to be used for calibration
int sensormax = 1023; //minimum sensor value when read from analogRead...to be used for calibration
int cycletime = 5000; //how much time between data collection periods (in milliseconds)
unsigned int addr=0;


void setup() {
  
  Serial.begin(9600); //initializes serial monitor (COMMAND+SHIFT+M) 
                      //in order to see data collection
  calibrate_sensors();

}
void loop() {

  read_data();
  save_data();
  //print_data();
  send_data();

  delay(cycletime);
   
}

void calibrate_sensors () { //calibrates sensors, to be done only when device turned on.

Xaccel = map(Zaccel, sensormin, sensormax, 0, 255);
Zaccel = map(Zaccel, sensormin, sensormax, 0, 255);

  
}

void read_data () {
 int Xaccel = analogRead(xpin) / 4; //reads the x-axis accelerometer input
 int Zaccel = analogRead(zpin) / 4; //reads the z-axis accelerometer input
 XaccelString = String(analogRead(xpin) / 4, 2); //reads the x-axis accelerometer input and makes string of 2 decimals
 ZaccelString = String(analogRead(zpin) / 4, 2); //reads the z-axis accelerometer input and makes string of 2 decimals
 Pressure = String(analogRead(pres) / 4, 2); //reads pressure sensor input and makes string of 2 decimals
 Temp = String(analogRead(temp) / 4, 2); //reads temp sensor input and makes string of 2 decimals

}

void save_data () { //saves data to local storage on downhole MCU
   
    if (Xaccel <= Xhigh || Zaccel >= Zhigh){ //when xaccel > value, take data point for pressure and temp

      String Data = String(XaccelString + " G" + "\t" + ZaccelString + " G" + "\t" + Pressure + " psi" + "\t" + Temp +" K");

      EEPROM.write(addr, Data);
      addr = addr+1;

      Serial.print(Data);
      
      //print_data();
    }
}

/*void print_data () { //prints to serial monitor if connected to computer...won't be used in actual testing. Simply a check
  Serial.print(Xaccel);
  Serial.print(" G");
  Serial.print("\t");
  Serial.print(Zaccel);
  Serial.print(" G");
  Serial.print("\t");
  Serial.print(Pressure);
  Serial.print(" PSI");
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(Temp);
  Serial.print(" K");
  Serial.print("\t");
  Serial.println();
}*/

void send_data () { //sends data to uphole MCU, not completed as of 2020/01/17
  
Serial.write("DATA");

  
}
