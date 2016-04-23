#include "mbed.h"
#include "Servo.h"
#include "robotDS.h"
#include <PwmOut.h>
Serial pc(USBTX, USBRX);


//*****************************************Connect to other mbed*******************************
AnalogIn collect(A0); //white
AnalogIn shoot(A1);   //brown


//**********************************collector system:*****************************************
//scooper dir/pwm
motor2 mScooper(D4, D3);

//collector dir,slp,pwm
motor1 mCollector(D9, D11, D10);


 void collectOff(){
     pc.printf("collect is low\n");
    mScooper.run2(0,0,0);  //dir,prd,seed
    mCollector.run1(0,1,0,0); //slp, dir, prd, speed
}

void collector(){
pc.printf("collect is high\n");
    mScooper.run2(0,.005f,.8f);  //dir,prd,seed
    mCollector.run1(1,1,.005f,.6f); //slp, dir, prd, speed

    //set collection time
    wait(15); //15
    collectOff();
}

//************************************shooting system*****************************************
Servo myservo(A5);

//DigitalOut motor(D6);
//PwmOut pwm(A4);
motor1 mShooter(D5, D6, D7);


//*****************************************off
void shootOff(){
     pc.printf("shoot is low\n");
    mShooter.run1(0,1,0,0);
}
//shooter interrupt
void shooter(){
pc.printf("shoot is high\n");
    mShooter.run1(1,0,.005f,.75f);  //slp, dir, prd, speed
    wait(.5);
    for(int i=0; i<=4;i++){
        myservo = 30;
        wait(.15);
        myservo = -20;
        //wait between each shot
        wait(1);
    }
   shootOff();
}



//***********************************************main*****************************************
int main()
{

    while (true) {
pc.printf("collect: %f\n", collect.read());
pc.printf("shoot: %f\n", shoot.read());
//collector();
     if(collect.read()>=.5){
          collector();
       }
      else if(shoot.read()>=.5){
           shooter();
        }
       else {
           collectOff();
           shootOff();

        }

       //if{
//            shooter();
//            pc.printf("shoot is high\n");
//        }
//        else if (shoot.read() ==0){
//            shootOff();
//            pc.printf("shoot is low\n");
//        }

    }
}
