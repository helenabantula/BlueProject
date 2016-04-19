#pragma once

#include "ofMain.h"
#include "Light.h"
#include "ofxGPIO.h"

#include "ofxXmlSettings.h"

//#define OF_ADDON_USING_OFXMLSETTINGS


enum StateType{
    
    STATE_IDLE,
    STATE_WARMING,
    STATE_PLAY,
    STATE_POSTPLAY,
    STATE_CRISIS
};


class ofApp : public ofBaseApp{

	public:
    
    
    StateType appState = STATE_IDLE;
    
    // TIME MANAGEMENT
    int counter;
    int warmingTime = 3;
    int maxErrorTime = 240; //4min
    int postPlayTime;
    int postPlayCounter;
    bool isCounterOn = true;
    
    
    // BUTTONS
    bool buttonON = false;
    bool buttonOFF = false;
    
    
    // LIGHT
    Light llum;
    
    
    //GPIO
    //GPIO gpio17;
//    GPIO gpio1;
//    GPIO gpio2;
//    GPIO gpio3;
    GPIO gpio4;
//    GPIO gpio5;
//    GPIO gpio6;
//    GPIO gpio7;
//    GPIO gpio8;
//    GPIO gpio9;
//    GPIO gpio10;
//    GPIO gpio11;
//    GPIO gpio12;
//    GPIO gpio13;
//    GPIO gpio14;
//    GPIO gpio15;
//    GPIO gpio16;
    GPIO gpio17;


//    string sate_button;
    
    string state_buttonON;
    string state_buttonOFF;

    

    void setup();
    void update();
    void draw();
    
    void idle();
    void warming();
    void play();
    void postPlay();
    void crisis();
    
    
    // Projecci— i XML ---------------------------------
    
    ofTrueTypeFont myfont;
    int middleX;
    int middleY;
    
    int spacing;
    
    int timer;
    int prevTimer;
    int digit1;
    int digit2;
    int digit3;
    
    string clock;
    
    
    ofxXmlSettings XML;

    //---------------------------------------------------
    
    

		
};
