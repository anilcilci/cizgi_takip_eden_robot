  #include <AFMotor.h>
  int r_motorV, l_motorV, m_motorV;
  int treshValue;
  AF_DCMotor l_motor(1, MOTOR12_64KHZ); 
  AF_DCMotor r_motor(2, MOTOR12_64KHZ); 
  int drc; // -1 -> sola , 1 -> sağa 0 -> düz
  int count;
  
  void setup() {
   Serial.begin(9600);
   treshValue = 250;
   drc = 0;
   
  }

  void runMotor( int left , int right  ){
      l_motor.setSpeed(left);
      l_motor.run(FORWARD);
      r_motor.setSpeed(right);
      r_motor.run(FORWARD);
    }

  void  turnDr( int drct ){
    readValues();

    if( (r_motorV > treshValue)&&((m_motorV > treshValue ) && (l_motorV > treshValue) ) ){
      
              if( drct == -1 ){
          
                  runMotor( 40 , 150 );
                
                }else if( drct == 1 ){
                  runMotor( 150 , 40 );  
                  }
              
              }// end of turnDr
              
              delay(5);
              
    }
  void readValues(){
    
        /*
          burada sensör değerleri okunup atanıyor...
        */
     r_motorV = analogRead(A8);
     m_motorV = analogRead(A9);
     l_motorV = analogRead(A10);

    }
   
  void loop() {
    
   readValues();
  

 /*  Serial.print( r1_motorV );

  Serial.print( "--" );
   
   Serial.print( m_motorV );

  Serial.print( "--" );
   
   Serial.print( l1_motorV );
  Serial.println( "  " );
*/

  if( (l_motorV > treshValue ) && (r_motorV > treshValue) ) {
       runMotor(140,140);
       //delay( 5 );
  } else if( (l_motorV< treshValue)&& (r_motorV > treshValue)  ){
       runMotor(30,140);
       delay( 5 );
       drc = -1;
       turnDr( drc );
       readValues();
       
       
  } else if( (l_motorV > treshValue)&& (r_motorV < treshValue) ){
       runMotor(140,30);
       delay( 5 );
       drc = 1;
       turnDr( drc );
       readValues();
       
  }  else if( r_motorV > treshValue && m_motorV > treshValue  && l_motorV > treshValue ){
       runMotor(0,0);
       delay( 5 );
       drc = 0;
       turnDr( drc );
  }
  /*
    else if(((r1_motorV< treshValue)&&(m_motorV < treshValue )) && (l1_motorV > treshValue)  )
  {
       l_motor.setSpeed(100);
       l_motor.run(FORWARD);
       r_motor.setSpeed(50);
       r_motor.run(FORWARD);
  }
      else if(((l1_motorV< treshValue)&&(m_motorV < treshValue )) && (r1_motorV > treshValue)  )
  {
       l_motor.setSpeed(50);
       l_motor.run(FORWARD);
       r_motor.setSpeed(100);
       r_motor.run(FORWARD);
  }
   else if( r1_motorV > treshValue && m_motorV > treshValue  && l1_motorV > treshValue )
  {
     //  l_motor.setSpeed(200);
       l_motor.run(RELEASE);
      // r_motor.setSpeed(175);
       r_motor.run(RELEASE);
  }
  delay(100);*/
  
  
  }
