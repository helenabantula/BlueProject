#pragma once

#include "ofMain.h"
#include "Light.h"

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
    
    
    // FILE
    ofFile file;
    ofBuffer dataBuffer;
    
    //file.open(ofToDataPath("results.xml"), ofFile::ReadWrite, false);

    void setup();
    void update();
    void draw();
    
    void idle();
    void warming();
    void play();
    void postPlay();
    void crisis();
    

		
};
