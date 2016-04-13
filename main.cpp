#include "mbed.h"
# include "robotDS.h"
Serial pc(USBTX, USBRX);

//Driving Motors
//dir,slp,pwm
motor1 mR(D13, D12, D11); //motor right wheel
motor1 mL(D5, D6, D7); //motor left wheel
motor2 mB(D10, D9); //motor back wheel

//driving functions
void left(){
    mR.run1(1,1,.005f, .3f);
    mL.run1(1,1,.005f, .3f);
    mB.run2(0,.005f, .15f);
    //wait(.01);
}
void right(){
    mR.run1(1,0,.005f, .3f);
    mL.run1(1,0,.005f, .3f);
    mB.run2(1,.005f, .15f);
    //wait(.01);
}
void forward(){
    mR.run1(1,1,.005f, .3f);
    mL.run1(1,0,.005f, .3f);
    mB.run2(1,.005f, 0);
    //wait(.01);
}
void stop(){
    mR.run1(1,1,0,0);
    mL.run1(1,0,0,0);
    mB.run2(1,0,0);
}

//BEACON SENSOR
max4617 maxChip(D3, D2, D1);
InterruptIn wave(A0); //output of beacon pcb
    //initialize constants
    float w = .25;  //delay for 8 max switches
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
//**************************** add switch pin: DigitalIn switchPin =

void freqDetector(){
    period = t1.read();
    freq = 1/period;
    t1.reset();
}

void maxRun(){
    maxChip.maxSwitch(0,0,0);
    t1.start();
    wait(w);
    freq0 = freq;
    maxChip.maxSwitch(1,0,0);
    t1.start();
    wait(w);
    freq1 = freq;
    maxChip.maxSwitch(0,1,0);
    t1.start();
    wait(w);
    freq2 = freq;
    maxChip.maxSwitch(1,1,0);
    t1.start();
    wait(w);
    freq3 = freq;
    maxChip.maxSwitch(0,0,1);
    t1.start();
    wait(w);
    freq4 = freq;
    maxChip.maxSwitch(1,0,1);
    t1.start();
    wait(w);
    freq5 = freq;
    maxChip.maxSwitch(0,1,1);
    t1.start();
    wait(w);
    freq6 = freq;
    maxChip.maxSwitch(1,1,1);
    t1.start();
    wait(w);
    freq7 = freq;
}

void checkFreqC(){
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
}

void checkFreqH(){
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
}

//Collector
DigitalOut collectorOut = D14;  //yellow
DigitalOut shootOut = D15; //green

//line sensor
DigitalIn lineSensor(PTE26);

int main()
{
    //center freq interrupt
    wave.rise(&freqDetector);

    //color selector
    // if (switchPin ==0){
    //     freqRed = freqRed;
    // }
    // else if (switchPin ==1){
    //     freqRed = freqBlue;
    // }

    while (true) {
        // 1. check center frequency
        maxRun();
        checkFreqC();

        //2. tape sensor
        //drive forward until tape sensor high
        while(lineSensor.read() == 1){
            forward();
            if (lineSensor.read() == 0){
                stop();
                break;
            }
        }
        // 3. Collect
        collectorOut = 1;
        wait(6);

        //4. check hoop frequency
        maxRun();
        checkFreqH();

        //5. Shoot
        shootOut = 1;
        wait(6);

    }
}
