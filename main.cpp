#include "mbed.h"
#include "robotDS.h"
Serial pc(USBTX, USBRX);

//button
//DigitalOut btnSet(D1);
//DigitalIn btnRead(D7);

InterruptIn sw2(SW2);
InterruptIn sw3(SW3);
//turn check
int turn =0;

DigitalOut led_red(LED_RED);
DigitalOut led_grn(LED_BLUE);

//*******************************************Driving Motors***********************************
//dir,slp,pwm or dir/pwm
motor2 mR(D13, D12); //motor right wheel
motor2 mL(D5, D6); //motor left wheel
motor1 mB(D9, D10, D11); //motor back wheel

//driving functions
void left(){
    mR.run2(0,.005f, .3f);
    mL.run2(1,.005f, .3f);
    mB.run1(1,1,.005f, .15f);
    //wait(.01);
}
void right(){
    mR.run2(1,.005f, .3f);
    mL.run2(0,.005f, .3f);
    mB.run1(1, 0,.005f, .15f);
    //
    wait(.01);
}
void forward(){
    mR.run2(0,.005f, .3f);
    mL.run2(0,.005f, .3f);
    mB.run1(0,1,.005f, 0);
    //wait(.01);
}
void stop(){
    mR.run2(1,0,0);
    mL.run2(0,0,0);
    mB.run1(0,1,0,0);
}

//*********************************************BEACON SENSOR**********************************
max4617 maxChip(D3, D2, D1);
InterruptIn wave(A0); //output of beacon pcb
    //initialize constants
    float w = .1;  //delay for 8 max switches
    Ticker tick;
    Timer t1;
    volatile float period =0;
    volatile float freq = 0;
    volatile float freq0 = 0;
    volatile float freq1 = 0;
    volatile float freq2 = 0;
    volatile float freq3 = 0;
    volatile float freq4 = 0;
    volatile float freq5 = 0;
    volatile float freq6 = 0;
    volatile float freq7 = 0;
    int waitTurn = .4;
    int waitTurnS = .4;

//hoop freq
volatile int freqRed = 1200;
volatile int freqBlue = 3000;


void freqDetector(){
    period = t1.read();
    freq = 1/period;
    //freq0 = 1/period;
    t1.reset();
}

//**************************************MAX CHIP******************************
void maxRunC(){
    maxChip.maxSwitch(0,0,0);
    t1.start();
    wait(w);
    freq0 = freq;
    //pc.printf("0: %f\n, freq0");
    maxChip.maxSwitch(1,0,0);
    t1.start();
    wait(w);
    freq1 = freq;
    //pc.printf("1: %f\n, freq1");
    maxChip.maxSwitch(0,1,0);
    t1.start();
    wait(w);
    freq2 = freq;
//    pc.printf("2: %f\n, freq2");
//    maxChip.maxSwitch(1,1,0);
//    t1.start();
//    wait(w);
//    freq3 = freq;
    //pc.printf("3: %f\n, freq3");
//    maxChip.maxSwitch(0,0,1);
//    t1.start();
//   wait(w);
//    freq4 = freq;
//    //pc.printf("4: %f\n, freq4");
//    maxChip.maxSwitch(1,0,1);
//    t1.start();
//    wait(w);
//    freq5 = freq;
//    pc.printf("5: %f\n, freq5");
    maxChip.maxSwitch(0,1,1);
    t1.start();
    wait(w);
    freq6 = freq;
    //pc.printf("6: %f\n, freq6");
    maxChip.maxSwitch(1,1,1);
    t1.start();
    wait(w);
    freq7 = freq;
    //pc.printf("7: %f\n, freq7");
//}

if ( ((freq1>=460) && (freq1<=540)) || ((freq2>=460) && (freq2<=540)) ){
    turn =1;
    led_red =0;
}
else if ( ((freq7>=460) && (freq7<=540)) || ((freq6>=460) && (freq6<=540)) ){
    turn =2;
    led_grn =0;
}

maxChip.maxSwitch(0,0,0);

while((freq0<=460) || (freq0>=540)){
   // forward();

    t1.start();
    wait(w);
    freq0 = freq;

    if (turn==1){
        left();
        led_grn=1;
        led_red =0;
    }
    else if (turn ==2){
        right();
        led_grn=0;
        led_red =1;
    }
}
stop();
//wait(2);
}

void maxRunH(){
   // maxChip.maxSwitch(0,0,0);
//    t1.start();
//    wait(w);
//    freq0 = freq;
//    //pc.printf("0: %f\n, freq0");
//    maxChip.maxSwitch(1,0,0);
//    t1.start();
//    wait(w);
//    freq1 = freq;
//    //pc.printf("1: %f\n, freq1");
    maxChip.maxSwitch(0,1,0);
    t1.start();
    wait(w);
    freq2 = freq;
//    pc.printf("2: %f\n, freq2");
    maxChip.maxSwitch(1,1,0);
    t1.start();
    wait(w);
    freq3 = freq;
    //pc.printf("3: %f\n, freq3");
    maxChip.maxSwitch(0,0,1);
    t1.start();
    wait(w);
    freq4 = freq;
    //pc.printf("4: %f\n, freq4");
 //   maxChip.maxSwitch(1,0,1);
//    t1.start();
//    wait(w);
//    freq5 = freq;
//    pc.printf("5: %f\n, freq5");
    maxChip.maxSwitch(0,1,1);
    t1.start();
    wait(w);
    freq6 = freq;
    //pc.printf("6: %f\n, freq6");
    maxChip.maxSwitch(1,1,1);
    t1.start();
    wait(w);
    freq7 = freq;
    //pc.printf("7: %f\n, freq7");
//}

//if ( ((freq2>=(freqRed-200)) && (freq2<=(freqRed+500))) || ((freq3>=(freqRed-200)) && (freq3<=(freqRed+500))) ){
//    turn =1;
//    led_red =0;
//}
//else if ( ((freq6>=(freqRed-200)) && (freq6<=(freqRed+500))) || ((freq7>=(freqRed-200)) && (freq7<=(freqRed+500))) ){
//    turn =2;
//    led_grn=0;
//}
//
//maxChip.maxSwitch(0,0,1);
//while( (freq4<=(freqRed-200)) || (freq4>=(freqRed+500)) ){
//    t1.start();
//    wait(w);
//    freq4 = freq;
//    if (turn==1){
//        right();
//        led_grn=1;
//        led_red =0;
//    }
//    else if (turn ==2){
//        left();
//        led_grn=0;
//        led_red =1;
//    }
//
//}

if ( ((freq2>=(freqRed-200)) && (freq2<=(freqRed+500))) || ((freq3>=(freqRed-200)) && (freq3<=(freqRed+500))) ){
    turn =1;
    led_red =0;
}
else if ( ((freq6>=(freqRed-200)) && (freq6<=(freqRed+500))) ){//(freq7>=(freqRed-200)) && (freq7<=(freqRed+500))) ){
    turn =2;
    led_grn=0;
}

maxChip.maxSwitch(0,0,1);
while( (freq4<=(freqRed-200)) || (freq4>=(freqRed+500)) ){
    t1.start();
    wait(w);
    freq4 = freq;
    if (turn==1){
        right();
        led_grn=1;
        led_red =0;
    }
    else if (turn ==2){
        left();
        led_grn=0;
        led_red =1;
    }

}


stop();

}

//*************************************Collector*********************************************
DigitalOut collectorOut = D14;  //white
DigitalOut shootOut = D15; //brown

//************************************line sensor*********************************************
DigitalIn lineSensor(PTE26);

//************************************button*********************************************
void red(){
    freqRed = freqRed;
}
void blue(){
    freqRed = freqBlue;
}

//***************************************MAIN*************************************************
int main()
{
    //center freq interrupt
    wave.rise(&freqDetector);
    sw2.rise(&red);
    sw3.rise(&blue);
  //  //color selector low==3000
//    if (btnRead.read() ==0){
//         freqRed = freqRed;
//     }
//     else if (btnRead.read() ==1){
//         freqRed = freqBlue;
//     }
    collectorOut=0;
    shootOut=0;
    while (true) {
          //color selector low==3000
//          pc.printf("switch: %f\n", btnRead.read());
//    if (btnRead.read() ==0){
//         freqRed = freqRed;
//     }
//     else if (btnRead.read() ==1){
//         freqRed = freqBlue;
//     }
       // while(0){
        // 1. check center frequency
        pc.printf("center freq\n");
        maxRunC();
        //checkFreqC();

        //2. tape sensor
        pc.printf("linesensor\n");
        //drive forward until tape sensor high
        while(lineSensor.read() == 1){
            forward();
//            if (lineSensor.read() == 0){
//                stop();
//                break;
//            }
        }
        wait(.75);
        stop();
       // wait(1);

        // 3. Collect
        pc.printf("collect\n");
        collectorOut = 1;
        wait(15); //15
        collectorOut = 0;

        //4. check hoop frequency
        pc.printf("hoop freq\n");
        maxRunH();

        //5. Shoot
        pc.printf("shoot\n");
        shootOut = 1;
        wait(1.5*4);
        shootOut = 0;
     //   }

    }
}
