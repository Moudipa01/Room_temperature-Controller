

 // Declare/assign Arduino IO-pins

  const int temp_trans_pin = A0, Heater_pin = 13, FAN_pin = 6;
 /*FAN_pin: here I used DC motor in stead of FAN because 
  I couldn't find the symbol for it. Similarly,for the
   Heater (Heater_pin), I used LED.*/

// Set the range of the desired temperature

   float MinTemp = 20, MaxTemp = 25;/*Room temperature is [20,25] degree C */

// Include the LCD library code

  #include <LiquidCrystal.h>

 // Initialize the library with the numbers of the interface pins
   
  LiquidCrystal LCD(12, 11, 5, 4, 3, 2);

  void setup() {
  
  // System initialization
    
    LCD.begin(16, 2);
    pinMode(Heater_pin, OUTPUT);//LED in our case
    pinMode(FAN_pin, OUTPUT);
    
  // Display the desired range of temperature
    
    LCD.print("Room temp(C):");
    LCD.setCursor(2,1);
    LCD.print(MinTemp); LCD.print("-");LCD.print(MaxTemp);
    
    delay(2000);
 }

 void loop() {
   
   float Eqv_volt, SensorTemp;
 
 // Read voltage and convert to temperature (Celsius)
   
   Eqv_volt = analogRead(temp_trans_pin) * 5.0 / 1023;
   SensorTemp = 100.0 * Eqv_volt-50.0;
    
  // Display the sensor reading
   
    LCD.clear();
    LCD.print("Sensor reading:");
    LCD.setCursor(2,1);
    LCD.print(SensorTemp); LCD.print(" C");
   
    delay(2000);
  
 /*Compare the sensor reading with the range of
  acceptable temperatures*/
  
   if(SensorTemp > MaxTemp){
      LCD.clear();
      LCD.print("temp is HIGHER!");//higher than the max
     
      /*Turn on FAN (dc motor)! to regulate the temp.
       Increase FAN speed at a slow rate*/
     
      LCD.setCursor(0, 1);LCD.print("Turn on FAN!");
      for( int i = 0; i <= 255; i++ ) {
        analogWrite(FAN_pin, i);
       }
       delay(2000);
     
       LCD.clear();
       LCD.print("Now temp is OK!");
       LCD.setCursor(0, 1);
       LCD.print("Turn off FAN!");
     
  // Turn off FAN slowly
       for( int i = 255; i >= 0; i-- ) {
        analogWrite(FAN_pin, i);
       }
        delay(2000);
       }
  else if(SensorTemp < MinTemp){
      LCD.clear();
      LCD.print("temp is LOWER!");//Less than the mini
      LCD.setCursor(0, 1);
      LCD.print("Turn on HEATER!");
    
     //Turn the heater ON, LED in our case 
    
      digitalWrite(Heater_pin, HIGH);
    
      delay(3000);
    
      LCD.clear();
      LCD.print("Now temp is OK!");
      LCD.setCursor(0, 1);
      LCD.print("Turn off HEATER!");
    
      delay(1000);
    
      digitalWrite(Heater_pin, LOW);
      LCD.clear();
      }
  else if(SensorTemp > MinTemp && SensorTemp < MaxTemp){/*Now temperature is perfect.
       That is,it is in the desired range. Hence no need of changes!!*/
      LCD.clear();
      LCD.print("Temp is NORMAL!");LCD.setCursor(2,1);
      LCD.print("Turn off all!");
    
      delay(1000);
      LCD.clear();
   }
  else {
      LCD.clear();
      LCD.print("Something went");
      LCD.setCursor(2,1); LCD.print("WRONG in the ckt");
      delay(1000);
      LCD.clear();
    }
    delay(1000);
   } 