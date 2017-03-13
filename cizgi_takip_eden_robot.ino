 #include <AFMotor.h>

  int rightSensor, leftSensor, middleSensor;
  int stableValue = 750;   //CNY70 sensörlerinde alınan değere göre siyah ve beyaz ayrımı için en stabil değer
  
  AF_DCMotor l_motor(1, MOTOR12_64KHZ); //Motor Sürücüsüne bağlı motorları nesne olarak üretiyoruz
  AF_DCMotor r_motor(2, MOTOR12_64KHZ); 
  
  int drc; // -1 -> sola , 1 -> sağa 0 -> düz
  int count;
  
  void setup() {
   Serial.begin(9600);
  
   drc = 0;
   
  }

  void runMotor( int left , int right  ){  //Motorlara çalışma komutunu verdiğimiz fonksiyon
      l_motor.setSpeed(left);       //Sol motorun gelen değere göre hızını ayarlayan komut
      l_motor.run(FORWARD);         //Sol motorun ileri yönde dönmesini sağlayan komut
      r_motor.setSpeed(right);
      r_motor.run(FORWARD);
    }

  void  turnDr( int drct ){
    readValues();     //Değerler okunur
    //Bu fonksiyon araç hızlı gelip dönüşü algıladıktan sonra çizgiden çıkarsa en son gördüğü dönüşe doğru dönmesini sağlar
    if( (rightSensor > stableValue)&&((middleSensor > stableValue ) && (leftSensor > stableValue) ) ){  //3 sensörde beyaz görüyorsa çalışır
      
              if( drct == -1 ){     //En son dönüş olup olmadığı sorgulanıyor
            
                  runMotor( 40 , 150 );
                
                }else if( drct == 1 ){
                  runMotor( 150 , 40 );  
                  }
              
              }
              
              delay(5);   //Ardunio'nun 5 milisaniye beklemesini sağlıyoruz
              
    }
  void readValues(){
    
        /*
          burada sensör değerleri okunup atanıyor...
        */
     rightSensor = analogRead(A8);
     middleSensor = analogRead(A9);
     leftSensor = analogRead(A10);
     
    }
   
  void loop() {
    
   readValues();
  


  if( (leftSensor > stableValue ) && (rightSensor > stableValue) ) { //Eğer sol ve sağ sensör beyaz algılıyorsa çalışır
       runMotor(140,140);                                            //2 motora eşit güç verilir
       
  } else if( (leftSensor < stableValue)&& (rightSensor > stableValue)  ){ //Eğer sol siyah sağ beyaz algılıyorsa çalışır
       runMotor(30,140);                                                  //Sola dönüş için sol motorun gücü düşürülür
       delay( 5 );
       drc = -1;                                                          //Direction değişkenin sola döndüğümüz için -1 değeri verilir
       turnDr( drc );                                                     //Fonksiyona yönlendirilir
       readValues();
       
       
  } else if( (leftSensor > stableValue)&& (rightSensor < stableValue) ){  //Sol sensör beyaz sağ siyah algılarsa çalışır
       runMotor(140,30);
       delay( 5 );
       drc = 1;
       turnDr( drc );
       readValues();
       
  }  else if( rightSensor > stableValue && middleSensor > stableValue  && leftSensor > stableValue ){  //Bütün sensörler beyaz algılarsa çizgi bitmiş olma ihtimalinden motorlar durdurulur. Diğer ihtimal turnDr() fonksiyonuyla çözülür.
       runMotor(0,0);
       delay( 5 );
       drc = 0;
       turnDr( drc );
  }

  
  }
