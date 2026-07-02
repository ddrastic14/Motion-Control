//Devant Yadav, Akuete Akwei, Charles Lejtman
//Works best with VLC Media Player  
#define VCC2  6 // define pin 6 as VCC2 (5V for left ultrasonic sensor)
#define VCC3  10// define pin 10 as VCC3 (5V for breadboard)
int ledPins[] = {7,8,9}; //pins used for digital output for LEDs
const int trigger1 = 2; //Trigger pin of left Sesnor
const int echo1 = 3; //Echo pin of left Sesnor
const int trigger2 = 4; //Trigger pin of right Sesnor
const int echo2 = 5;//Echo pin of right Sesnor

long time_taken; //time it takes for ultrasonic wave to hit target and come back to sensor
int dist,distL,distR; //dist used to store formula for calculating distance, distL and distR store distances from left and right sensors

void setup() {
  
   pinMode(VCC2,OUTPUT);//define pin 6 as output
  digitalWrite(VCC2, HIGH);// set pin 6 as HIGH so it acts as 5V
  pinMode(VCC3,OUTPUT);//define pin 10 as output
  digitalWrite(VCC3, HIGH);// set pin 10 as HIGH so it acts as 5V

  int index;

Serial.begin(9600); //Baud rate that arduino reads code at
pinMode(trigger1, OUTPUT); //set trigger on left sensor as output
pinMode(echo1, INPUT); //set echo on left sensor as input
pinMode(trigger2, OUTPUT); //set trigger on right sensor as output
pinMode(echo2, INPUT); //set echo on right sensor as input

// loop through array of LED pins so that we can call individual pins to turn them on or off in our loop() function
for(index = 0; index <= 2; index++)

{

pinMode(ledPins[index],OUTPUT);



}
  

}

//Function used to calculate hand distance from ultrasonic sensors
void calculate_distance(int trigger, int echo)
{
digitalWrite(trigger, LOW);
delayMicroseconds(2);
digitalWrite(trigger, HIGH);
delayMicroseconds(10);
digitalWrite(trigger, LOW);

time_taken = pulseIn(echo, HIGH); //time it takes for ultrasonic wave to hit target and come back to sensor
dist= time_taken*0.034/2; //formula to calculate distance
if (dist>50) //hand distance will not be measured beyond 50 cm
dist = 50;
}

void loop() {
  calculate_distance(trigger1,echo1);
distL =dist; //get distance of left sensor

calculate_distance(trigger2,echo2);  
distR =dist; //get distance of right sensor

//Logs distances of left and right hand from sensors to console in real time
Serial.print("L=");
Serial.println(distL);
Serial.print("R=");
Serial.println(distR);


//Play/Pause Mode (Both Hands)
if ((distL >30 && distR>30) && (distL <50 && distR<50)) //Detect both hands
{
  digitalWrite(ledPins[1], HIGH); //Turn on middle LED, to indicate both hands detected
delay(1000);
digitalWrite(ledPins[1], LOW);
//Other LEDs switched off
digitalWrite(ledPins[0], LOW);
digitalWrite(ledPins[2], LOW);
  Serial.println("Play/Pause");
}

//Get distances from both sensors
calculate_distance(trigger1,echo1);
distL =dist;

calculate_distance(trigger2,echo2);
distR =dist;

 

//Control Volume (Left Hand)
if (distL>=13 && distL<=17)
{
  digitalWrite(ledPins[0], HIGH); //Turn on left-most LED, to indicate left hand has been detected
     //Other LEDs switched off
     //Keeping LED on for 1 second delays program, gives user time to decide which action they want to perform
     delay(1000);
digitalWrite(ledPins[0], LOW);
     digitalWrite(ledPins[1], LOW);
      digitalWrite(ledPins[2], LOW); //Hold left hand between 13 and 17 cm in front of left sensor for hand to be detected
       Serial.println("Hand Detected");
  calculate_distance(trigger1,echo1);
  distL =dist;
 
   
   
    while(distL<50)
    {
      calculate_distance(trigger1,echo1);
      distL =dist;
      if (distL<10) //Hand pushed in raises volume
      {Serial.println ("Vup"); delay (300);}     
        if (  distL>20) //Hand pulled out lowers volume
      {Serial.println ("Vdown"); delay (300);}
      
    }
  
}    

//Control Fast Forward/Rewind (Right Hand)
if (distR>=13 && distR<=17)
{
  digitalWrite(ledPins[2], HIGH); //Turn on right-most LED to indicate right hand has been detected
    //Other LEDs switched off
    //Keeping LED on for 1 second delays program, gives user time to decide which action they want to perform
    delay(1000);
digitalWrite(ledPins[2], LOW);
    digitalWrite(ledPins[1], LOW);
    digitalWrite(ledPins[0], LOW); //Hold right hand between 13 and 17 cm in front of right sensor for hand to be detected
    Serial.println("Hand Detected");
  calculate_distance(trigger2,echo2);
  distR =dist;
 
    
    
    while(distR<50)
    {
      calculate_distance(trigger2,echo2);
      distR =dist;
      if (distR<10) //Right hand pushed in rewinds video
      {Serial.println ("Rewind"); delay (300);}
      if (distR>20) //Right hand pulled out fast forwards video
      {Serial.println ("Forward"); delay (300);}
      
  }

}

delay(200);

}
