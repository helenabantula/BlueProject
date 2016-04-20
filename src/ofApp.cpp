#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    Light::getInstance().initialize();      // Els pars es posen tots a tope
    Light::getInstance().fadePars(1, 'O', '0', warmingTime, "noButtonPars");
    
    
    //projecci—--------------------
    
    //ofTrueTypeFont::setGlobalDpi(150);

    //myfont.load("roboto.ttf", 300);

    //myfont.load("gt-walsheim-bold.ttf", 100,false,true);
    myfont.load("gt-walsheim-bold.ttf",50);
    
    //myfont.load("Montserrat-Bold.otf", 300);

    middleX = ofGetWidth()/2;
    middleY = ofGetHeight()/2;
    
    spacing = 300;
    //--------------------
    
    ofxXmlSettings dataLog;
    dataLog.setValue("User1:time", 10);
    dataLog.setValue("User1:color", "blue");
    dataLog.setValue("User1:day", std::to_string(ofGetDay()));
    dataLog.setValue("User1:hour", std::to_string(ofGetHours()) + "." + std::to_string(ofGetMinutes()));

    dataLog.saveFile("Log_BlueProject_" + std::to_string(ofGetDay()) + "_"
                                        + std::to_string(ofGetHours()) + "h"
                                        + std::to_string(ofGetMinutes()) + ".xml");
    
    //GPIO----------------------------
//    gpio17.setup("17");
//    gpio17.export_gpio();
//    gpio17.setdir_gpio("in");
//    
//    gpio4.setup("4");
//    gpio4.export_gpio();
//    gpio4.setdir_gpio("in");

//    gpio1.setup("1");
//    gpio2.setup("2");
//    gpio3.setup("3");
//    gpio4.setup("4");
//    gpio5.setup("5");
//    gpio6.setup("6");
//    gpio7.setup("7");
//    gpio8.setup("8");
//    gpio9.setup("9");
//    gpio10.setup("10");
//    gpio11.setup("11");
//    gpio12.setup("12");
//    gpio13.setup("13");
//    gpio14.setup("14");
//    gpio15.setup("15");
//    gpio16.setup("16");
//    gpio17.setup("17");


}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    timer = ofGetElapsedTimef();
    
    digit2 = (timer % 100) /10;
    digit3 = timer % 10;
    
    if (timer % 60 == 0 && timer!= prevTimer)
        digit1 +=1;
    
    prevTimer = ofGetElapsedTimef();
    
    
    clock = std::string("0")+std::to_string(digit1)+":"+std::to_string(digit2)+std::to_string(digit3);
    
    
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
    
    
    //cout <<"HO ESTIC FENT BE"<< endl;
    
    
//    int valorGPIOon;
//    valorGPIOon = gpio17.getval_gpio(state_buttonON);
//    cout <<"ON : "+ state_buttonON << endl;
    //ofLog()<<state_button;
    //usleep(50000);
    
//    int valorGPIOoff;
//    valorGPIOoff = gpio4.getval_gpio(state_buttonOFF);
//    cout <<"OFF : " + state_buttonOFF << endl;
    
//    string sate_button;

    //int valorGPIO;
    
//    valorGPIO = gpio1.getval_gpio(state_buttonOFF);
//    cout <<"Gpio1 : " + state_buttonOFF << endl;
//    
//    valorGPIO = gpio2.getval_gpio(state_buttonOFF);
//    cout <<"Gpio2 : " + state_buttonOFF << endl;
//    
//    valorGPIO = gpio3.getval_gpio(state_buttonOFF);
//    cout <<"Gpio3 : " + state_buttonOFF << endl;
//    
//   valorGPIO = gpio4.getval_gpio(state_buttonON);
//   cout <<"Gpio4 : " + state_buttonON << endl;
//
//    valorGPIO = gpio5.getval_gpio(state_buttonOFF);
//    cout <<"Gpio5 : " + state_buttonOFF << endl;
//    
//    valorGPIO = gpio6.getval_gpio(state_buttonOFF);
//    cout <<"Gpio6 : " + state_buttonOFF << endl;
//    
//    valorGPIO = gpio7.getval_gpio(state_buttonOFF);
//    cout <<"Gpio7 : " + state_buttonOFF << endl;
//    
//    valorGPIO = gpio8.getval_gpio(state_buttonOFF);
//    cout <<"Gpio8 : " + state_buttonOFF << endl;
//    
//    valorGPIO = gpio9.getval_gpio(state_buttonOFF);
//    cout <<"Gpio10 : " + state_buttonOFF << endl;
//    
//    valorGPIO = gpio10.getval_gpio(state_buttonOFF);
//    cout <<"Gpio11 : " + state_buttonOFF << endl;
//    
//    valorGPIO = gpio11.getval_gpio(state_buttonOFF);
//    cout <<"Gpio12 : " + state_buttonOFF << endl;
//    
//    valorGPIO = gpio12.getval_gpio(state_buttonOFF);
//    cout <<"Gpio13 : " + state_buttonOFF << endl;
//    
//    valorGPIO = gpio13.getval_gpio(state_buttonOFF);
//    cout <<"Gpio14 : " + state_buttonOFF << endl;
//    
//    valorGPIO = gpio14.getval_gpio(state_buttonOFF);
//    cout <<"Gpio15 : " + state_buttonOFF << endl;
//    
//    valorGPIO = gpio15.getval_gpio(state_buttonOFF);
//    cout <<"Gpio16 : " + state_buttonOFF << endl;
//    
//    valorGPIO = gpio16.getval_gpio(state_buttonOFF);
//    cout <<"Gpio1 : " + state_buttonOFF << endl;
    
//    valorGPIO = gpio17.getval_gpio(state_buttonOFF);
//    cout <<"Gpio17 : " + state_buttonOFF << endl;
    
    
    //usleep(50000);

    
    
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
void ofApp::draw()
{
    ofBackground(0);
    
   myfont.drawString(clock, middleX-400,middleY);
    
    //ofDrawBitmapString("Helena",10,10);
    
    //ofDrawBitmapString(clock,middleX,middleY,100);
    
   // myfont.drawString("Helena",10,10);

}
