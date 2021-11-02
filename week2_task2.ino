/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */

#include <ros.h>
#include <std_msgs/String.h>

int inter1 = 2 ;
int inter2 = 3 ;
double count = 0 ;
ros::NodeHandle  nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char * message = "hello world!";

void setup()
{
  nh.initNode();
  nh.advertise(chatter);
  pinMode(inter1,INPUT_PULLUP);
  pinMode(inter1,INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(inter1),ISR_A,CHANGE);
  attachInterrupt(digitalPinToInterrupt(inter2),ISR_B,CHANGE);
}

void loop()
{
  message = toArray(count);
  str_msg.data = message;
  
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(1000);
}

void ISR_A()
{
 if(digitalRead(inter1) != digitalRead(inter2))
 count++;
 else 
 count--;

}
void ISR_B()
{
 if(digitalRead(inter1) == digitalRead(inter2))
 count++;
 else 
 count--;

}
char * toArray(int number)
{
    int n = log10(number) + 1;
    int i;
    char *numberArray = calloc(n, sizeof(char));
    for (i = n-1; i >= 0; --i, number /= 10)
    {
        numberArray[i] = (number % 10) + '0';
    }
    return numberArray;
}
