#pragma once

#include "ofMain.h"
#include "Light.h"
#include "ofxGPIO.h"  //<<<<----------------------------DESCOMENTAR!!!!!!!!!!!!!!!!!!!!

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
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    StateType appState = STATE_IDLE;
    
    // TIME MANAGEMENT
    
    
    int counter; //temps d'inici de comptador
    int finalCounter; //interval de temps passat quan es para el comptador
    
    
    
    int warmingTime = 3;
    int maxErrorTime = 15;//240; //4min
    int postPlayTime = 5;
    int postPlayCounter;
    bool isCounterOn = false;
    
    
    // BUTTONS
    bool buttonON = false;
    bool buttonOFF = false;
    
    
    // LIGHT
    Light llum;
    
    
    //GPIO

    GPIO gpio21;
    GPIO gpio17;
    string state_buttonON;
    string state_buttonOFF;
    string state_button;




    

    void setup();
    void update();
    void draw();
    
    void idle();
    void warming();
    void play();
    void postPlay();
    void crisis();
    
    void saveData();

    
    
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
    
    
    ofxXmlSettings dataLog;
    int userIndex;

    //---------------------------------------------------
    
    		
};
