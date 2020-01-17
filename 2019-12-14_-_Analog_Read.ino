int xpin = A2;
int zpin = A1;
int pres = A4;
int temp = A5;

int Xhigh = 1;
int Zhigh = 1;
int TimeStep = 100;


void setup() {
  Serial.begin(9600);

}

void loop() {
  for (int i = 0; i<100; i+1 ) {
    

    int sensorx = analogRead(xpin);
    int sensorz = analogRead(zpin);
    int sensorpres = analogRead(pres);
    int temppres = analogRead(temp);

    float Xaccel = (sensorx-500.00)/250;
    float Zaccel = (sensorz-500.00)/250;

    
    Serial.print(Xaccel);
    Serial.print(" G");
    Serial.print("\t");
    Serial.print("\t");
    Serial.print(Zaccel);
    Serial.print(" G");
    Serial.print("\t");
    
    float R = 10000.0 / ((1023.0/temppres));
    float Tempinverse = (1/298.20) + (1/1000) * log(R/10000.00);
    float Temp = 1/(Tempinverse);

    float Pressure = 29-sensorpres;
    
    
    if (Xaccel <= Xhigh || Zaccel >= Zhigh){ //when xaccel > value, take data point for pressure and temp
      Serial.print("\t");
      Serial.print(Pressure);
      Serial.print(" PSI");
      Serial.print("\t");
      Serial.print("\t");
      Serial.print(Temp);
      Serial.print(" K");
      Serial.print("\t");
      Serial.print(R);
      Serial.print(" ohms");
    }
    /*if(Zaccel >= Zhigh){
      Serial.print("\t");
      Serial.print(Pressure);
      Serial.print(" PSI");
      Serial.print("\t");
      Serial.print("\t");
      Serial.print(Temp);
      Serial.print(" K");
    }*/
    Serial.println();
    delay(TimeStep);
   }
}
