#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <NewPing.h>

SoftwareSerial mySerial(10, 9);

AF_DCMotor motor(1);
AF_DCMotor motor2(2);

#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
int i;
bool prox;
int distance;

void setup() 
{
  mySerial.begin(9600);
  Serial.begin(9600);
  motor.setSpeed(200);
  motor.run(RELEASE);
}

void sendCommand(const char* command) 
{
  Serial.print("Command send :");
  Serial.println(command);
  mySerial.println(command);
  delay(500);

  char reply[100];
  int i=0;
  while (mySerial.available()) 
  {
    reply[i]=mySerial.read();
    i+=1;
  }
    
  reply[i]='\0';
  Serial.print(reply);
  Serial.println("Reply successful");
}

void sensor_read()
{
  distance=sonar.ping_cm();
  Serial.println(distance);
  if (distance>10 or distance==0)
  {
    Serial.println("No obstruction");
    prox=false;
  }
  else
  {
    Serial.println("Obstruction");
    prox=true;
  }
}

char readSerial() 
{
  char reply[100];
  int i=0;
  while (mySerial.available()) 
  {
    reply[i]=mySerial.read();
    i+=1;
  }
  reply[i]='\0';

  if (strlen(reply)>0) 
  {
    Serial.println("reply");
    Serial.println(reply);
  }

  return reply[0];
}

void loop() 
{
  char reply=readSerial();
  sensor_read();

  if (prox==false)
  {
    if (reply=='f')
    {
      Serial.println("forward");
      motor.run(FORWARD);
      for (i=0; i<255; i++) 
      {
        motor.setSpeed(i);  
        delay(10);
      }
      for (i=255; i!=0; i--) 
      {
        motor.setSpeed(i);  
        delay(10);
      }
    }
    else if (reply=='b')
    {
      Serial.println("backward");
      motor.run(BACKWARD);
      for (i=0; i<255; i++) 
      {
        motor.setSpeed(i);  
        delay(10);
      }
      for (i=255; i!=0; i--) 
      {
        motor.setSpeed(i);  
        delay(10);
      }
    }
    else if (reply=='s')
    {
      Serial.println("stop");
      motor.run(RELEASE);
    }
    else
      motor.run(RELEASE);
  }

  delay(500);
}
