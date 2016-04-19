#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    Light::getInstance().initialize();      // Els pars es posen tots a tope
    Light::getInstance().fadePars(1, 'O', '0', warmingTime, "noButtonPars");

}

//--------------------------------------------------------------
void ofApp::update(){
    
    switch(appState){
        case STATE_IDLE:
            idle();
            break;
        case STATE_WARMING:
            warming();
            break;
        case STATE_PLAY:
            play();
        case STATE_POSTPLAY:
            postPlay();
            break;
        case STATE_CRISIS:
            crisis();
            break;
    }
    
    
    Light::getInstance().getInfo();
    
}

//--------------------------------------------------------------
void ofApp::idle(){
    
    if (buttonON) {
        isCounterOn = true;
        
        Light::getInstance().changeColor();
        Light::getInstance().fadePars(1,'O', 1, warmingTime, "buttonPars"); //no hauria de ser warming time!!
        Light::getInstance().fadePars(1, 'I', '0', warmingTime, "all");     //no hauria de ser warming time!!
        
        appState = STATE_WARMING;
        
    }
    
}

//--------------------------------------------------------------
void ofApp::warming(){
    
    if ((ofGetElapsedTimef() - counter) == warmingTime) {
        appState = STATE_PLAY;
    }
    
    // IMPLEMENT CRISIS
    
}


//--------------------------------------------------------------
void ofApp::play(){
    
    if (buttonOFF) {
        
        // SAVE DATA:
        //dataBuffer = (string)counter;
        //ofBufferToFile("data.dat", dataBuffer);
        
        isCounterOn = false;
        
        postPlayCounter = ofGetElapsedTimef();
        appState = STATE_POSTPLAY;
        
        Light::getInstance().fadePars(1, 'O', 1, postPlayTime, "noButtonPars");
        
    }
    
    if ((ofGetElapsedTimef() - counter) == maxErrorTime) {                // no escrius?
        // SAVE DATA?
        appState = STATE_IDLE;
    }
    
    
}


//--------------------------------------------------------------
void ofApp::postPlay(){
    
    if ((ofGetElapsedTimef() - postPlayCounter) == postPlayTime) {
        appState = STATE_IDLE;
        // SET counter TO 0!!
    }
    
}

//--------------------------------------------------------------
void ofApp::crisis(){
    // IMPLEMENTAR!
    
    
}



//--------------------------------------------------------------
void ofApp::draw(){

}
