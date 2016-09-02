#include <SoftwareSerial.h>


/* This following program uses HC-05 to get information from the user 
 *  via bluetooth and performs task based on the given input.
 *  
 *  To know more about HC-05 configuration check out the link below
 *  https://arduino-info.wikispaces.com/BlueTooth-HC05-HC06-Modules-How-To
 *  
 *  I used a level shifter here , which is connected 
 *  
 *  Transmitter of arduino pin ( softwareSerial Tx ) is directly connected to HV of the level shifter and
 *  to the Rx of the HC-05
 */

// Variable declaration
# define TxPin 6
# define RxPin 7

char recievedData  ;

const byte LEDpin = 3;
const byte RLED = 9;
const byte GLED = 10;
const byte BLED = 11;

// String declaration

void RGB(int R ,byte PIN1PWM, int G, byte PIN2PWM , int B , byte PIN3PWM );

// Class object
SoftwareSerial mySerial ( RxPin , TxPin );

void setup ()
{ 
  pinMode ( RLED , OUTPUT );
  pinMode ( GLED , OUTPUT );
  pinMode ( BLED , OUTPUT );
  
  pinMode ( LEDpin , OUTPUT );
  // Rx is input 
  pinMode ( RxPin , INPUT );
  // Tx is output 
  pinMode ( TxPin , OUTPUT );
  Serial.begin(19200);
  mySerial.begin(9600);

boolean REDvalue = 0;
boolean GREEDvalue = 0;
boolean BLUEvalue = 0;

}

void loop ()
{
  if ( Serial.available() > 0 )
  {
  recievedData = Serial.read(); 
  Serial.println(recievedData);
  }
  delay(100);
   switch ( recievedData )
  {
    case 'r' :

     // RGB ( REDLED , PWM_value for RED , GREENLED , PWM_value for green , BLUELED , PWM_value for blue led );
     RGB ( 1,0 , 0,0 , 0,0 );
    break;
    case 'g' :

     RGB ( 0,0 , 1,0 ,0,0 );
    break;
    case 'b' :
    
      RGB ( 0,0 , 0,0 ,1,0 );
    break;
    case 'p' :
      RGB ( 1,255 , 0,0 ,1,127); // Pink
      break;
    case 'n' :
      RGB ( 0 ,0 , 1 , 255 , 1 ,128 ); // Light Green
       break ;
    case 'y' :
      RGB ( 1,255 , 1,255 , 1,102 );  // yellow
      break;
    case 'h' : // LED HIGH
    digitalWrite ( LEDpin , HIGH );
    break;
    case 'l' :  // LED LOW
    digitalWrite ( LEDpin , LOW );
    break;
    }// close switch
    
}// close loop

void RGB(int R ,byte PIN1PWM, int G, byte PIN2PWM , int B , byte PIN3PWM )
{ 
  if ( R==1 && G==0 && B==0 ) // Light ups only RED LED
  {
  digitalWrite( RLED , HIGH );
  digitalWrite ( GLED , LOW );
  digitalWrite ( BLED , LOW );
  }
  
  else if (  R==0 && G==1 && B==0 ) // Light ups only GREEN LED
  {
  digitalWrite( RLED , LOW );
  digitalWrite ( GLED , HIGH );
  digitalWrite ( BLED , LOW );
  }
  else if ( R==0 && G==0 && B==1) // Light ups only blue led
  { 
  digitalWrite ( RLED , LOW );
  digitalWrite ( GLED , LOW );
  digitalWrite( BLED , HIGH);
  }
  else if ( R==1 && G==0 && B==1 )  // Light ups any colour combination using R and B
  {
  analogWrite ( RLED , PIN1PWM  );
  digitalWrite ( GLED , LOW );
  analogWrite( BLED , PIN3PWM );
  }
  else if ( R==0 && G==0 && B==1) // Light ups only blue led
  { 
  digitalWrite ( RLED , LOW );
  digitalWrite ( GLED , LOW );
  digitalWrite( BLED , HIGH);
  }
  else if ( R== 1 && G==1 && B==1 ) // Light ups any color using all the 3 LED
  {
    analogWrite ( RLED , PIN1PWM );
    analogWrite ( GLED , PIN2PWM );
    analogWrite ( BLED , PIN3PWM );
  }
  else if ( R==0 && G==1 && B==1 )
  {
    digitalWrite ( RLED , LOW);
    analogWrite ( GLED , PIN2PWM );
    analogWrite ( BLED , PIN3PWM );
  }
  
}


