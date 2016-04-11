#include "mbed.h"
Serial pc(USBTX, USBRX);

//DRIVING
//Motor 1 (right)
DigitalOut DIR1(D13); //direction
PwmOut STP1(D11); //PWM
DigitalOut SLP1(D12); //sleep
//Motor 2 (left)
DigitalOut DIR2(D5); //direction
PwmOut STP2(D7); //PWM
DigitalOut SLP2(D6); //sleep
//Motor 3 (back)
DigitalOut DIR3(D10); //direction
PwmOut STP3(D9); //PWM

void left(){
    SLP1 =1;
    DIR1 = 1;
    STP1.period(.005f);

    SLP2 =1;
    DIR2 = 1;
    STP2.period(.005f);


    STP3.period(.005f);
    DIR3 = 0;

    STP2.write(.3f);
    STP1.write(.3f);
    STP3.write(.15f);

    wait(.01);
}
void right(){
    SLP1 =1;
    DIR1 = 0;
    STP1.period(.005f);

    SLP2 =1;
    DIR2 = 0;
    STP2.period(.005f);


    STP3.period(.005f);
    DIR3 = 1;

    STP2.write(.3f);
    STP1.write(.3f);
    STP3.write(.15f);

    wait(.01);
}
void forward(){
    pc.printf("forward\n");

    SLP1 =1;
    DIR1 = 1;
    STP1.period(.005f);

    SLP2 =1;
    DIR2 = 0;
    STP2.period(.005f);


//    STP3.period(.005f);
//    DIR3 = 1;
//
    STP2.write(.3f);
    STP1.write(.3f);
    //STP3.write(.4f);

    wait(.01);
}
void stop(){
    STP1.write(0);
    STP2.write(0);
    STP3.write(0);
}

//BEACON SENSOR
DigitalOut pinA = D3; //purple
DigitalOut pinB = D2;
DigitalOut pinC = D1;
InterruptIn wave(A0); //output of beacon pcb

float w = .25;
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
int freqRed = 1200;
int freqBlue = 3000;

void freqDetector(){

    period = t1.read();
    freq = 1/period;
    t1.reset();
}

//Collector
DigitalOut collectorOut = D14;  //yellow
DigitalOut shootOut = D15; //green

int main()
{
    t1.start();
    wave.rise(&freqDetector);


    while (true) {



//        //test
//        forward();
//
//        wait(4);
//        stop();
//        right();
//        pc.printf("right1\n");
//        wait(4);
//        stop();
//        left();
//        pc.printf("left1\n");
//        wait(4);
// stop();
// wait(2);

        //check center frequency
            pinA = 0;
            pinB = 0;
            pinC = 0;
            pc.printf("Period = %f Frequency0=%f\n", period,1/period);
            wait(w);
            freq0 = freq ;
            pinA = 1;
            pinB = 0;
            pinC = 0;
            pc.printf("Period = %f Frequency1=%f\n", period,1/period);
            wait(w);
            freq1 = freq ;
            pinA = 0;
            pinB = 1;
            pinC = 0;
            pc.printf("Period = %f Frequency2=%f\n", period,1/period);
            wait(w);
            freq2 = freq;
            pinA = 1;
            pinB = 1;
            pinC = 0;
            pc.printf("Period = %f Frequency3=%f\n", period,1/period);
            wait(w);
            freq3 = freq;
            pinA = 0;
            pinB = 0;
            pinC = 1;
            pc.printf("Period = %f Frequency4=%f\n", period,1/period);
            wait(w);
            freq4 = freq;
            pinA = 1;
            pinB = 0;
            pinC = 1;
            pc.printf("Period = %f Frequency5=%f\n", period,1/period);
            wait(w);
            freq5 = freq;
            pinA = 0;
            pinB = 1;
            pinC = 1;
            pc.printf("Period = %f Frequency6=%f\n", period,1/period);
            wait(w);
            freq6 = freq;
            pinA = 1;
            pinB = 1;
            pinC = 1;
            pc.printf("Period = %f Frequency7=%f\n", period,1/period);
            wait(w);
            freq7 = freq;


        if ((freq0>=460) && (freq0<=540)){
            //
            pc.printf("No turning\n");
        }
        else if((freq1>=460) && (freq1<=540)){
            right();
            pc.printf("turning1\n");
            wait(waitTurn);
            stop();
        }
        else if((freq2>=460) && (freq2<=540)){
            right();
            pc.printf("turning2\n");
            wait(waitTurn*2);
            stop();
        }
        else if((freq3>=460) && (freq3<=540)){
            right();
            pc.printf("turning3\n");
            wait(waitTurn*3);
            stop();
        }
        else if((freq4>=460) && (freq4<=540)){
            right();
            pc.printf("turning4\n");
            wait(waitTurn*4);
            stop();
        }
        else if((freq5>=460) && (freq5<=540)){
            left();
            pc.printf("turning5\n");
            wait(waitTurn*3);
            stop();
        }
        else if((freq6>=460) && (freq6<=540)){
            left();
            pc.printf("turning6\n");
            wait(waitTurn*2);
            stop();
        }
        else if((freq7>=460) && (freq7<=540)){
            left();
            pc.printf("turning7\n");
            wait(waitTurn);
            stop();
        }
        //drive forward until tape sensor high
        forward();
        wait(6);
        stop();
        //collect
        collectorOut = 1;
        pc.printf("collecting\n");
        wait(6);

        //check hoop frequency
            pinA = 0;
            pinB = 0;
            pinC = 0;
            pc.printf("Period = %f Frequency0=%f\n", period,1/period);
            wait(w);
            freq0 = freq ;
            pinA = 1;
            pinB = 0;
            pinC = 0;
            pc.printf("Period = %f Frequency1=%f\n", period,1/period);
            wait(w);
            freq1 = freq ;
            pinA = 0;
            pinB = 1;
            pinC = 0;
            pc.printf("Period = %f Frequency2=%f\n", period,1/period);
            wait(w);
            freq2 = freq;
            pinA = 1;
            pinB = 1;
            pinC = 0;
            pc.printf("Period = %f Frequency3=%f\n", period,1/period);
            wait(w);
            freq3 = freq;
            pinA = 0;
            pinB = 0;
            pinC = 1;
            pc.printf("Period = %f Frequency4=%f\n", period,1/period);
            wait(w);
            freq4 = freq;
            pinA = 1;
            pinB = 0;
            pinC = 1;
            pc.printf("Period = %f Frequency5=%f\n", period,1/period);
            wait(w);
            freq5 = freq;
            pinA = 0;
            pinB = 1;
            pinC = 1;
            pc.printf("Period = %f Frequency6=%f\n", period,1/period);
            wait(w);
            freq6 = freq;
            pinA = 1;
            pinB = 1;
            pinC = 1;
            pc.printf("Period = %f Frequency7=%f\n", period,1/period);
            wait(w);
            freq7 = freq;

        if ((freq0>=freqRed-200) && (freq0<=freqRed+500)){
            left();
            pc.printf("turning0\n");
            wait(waitTurnS*4);
            stop();
        }
        else if((freq1>=freqRed-200) && (freq1<=freqRed+500)){
            left();
            pc.printf("turning1\n");
            wait(waitTurnS*3);
            stop();
        }
        else if((freq2>=freqRed-200) && (freq2<=freqRed+500)){
            left();
            pc.printf("turning2\n");
            wait(waitTurnS*2);
            stop();
        }
        else if((freq3>=freqRed-200) && (freq3<=freqRed+500)){
            left();
            pc.printf("turning3\n");
            wait(waitTurnS);
            stop();
        }
        else if((freq4>=freqRed-200) && (freq4<=freqRed+500)){
            //
            pc.printf("No turning\n");
        }
        else if((freq5>=freqRed-200) && (freq5<=freqRed+500)){
            right();
            pc.printf("turning5\n");
            wait(waitTurn);
            stop();
        }
        else if((freq6>=freqRed-200) && (freq6<=freqRed+500)){
            right();
            pc.printf("turning6\n");
            wait(waitTurn*2);
            stop();
        }
        else if((freq7>=freqRed-200) && (freq7<=freqRed+500)){
            right();
            pc.printf("turning7\n");
            wait(waitTurn*3);
            stop();
        }
        //shoot
        shootOut = 1;
        pc.printf("shooting\n");
        wait(6);





    }
}
