#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    ////////////////////////// SERIAL ////////////////////////
    ofSetVerticalSync(true);
    int baud = 9600;
    
    
    serial.listDevices();
    
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
#if TARGET_RASPBERRY_PI
    serial.setup(0, baud);
#else
    serial.setup("/dev/cu.usbmodem1421",baud);
#endif
    
    
    ofHideCursor();
    
    Light::getInstance().initialize();      // Els pars es posen tots a tope
    Light::getInstance().fadePars(1, 'O', '0', warmingTime, 3);
    
    
    //projecci—--------------------
    
    ofTrueTypeFont::setGlobalDpi(150);

    //myfont.load("roboto.ttf", 300);

    //myfont.load("gt-walsheim-bold.ttf", 100,false,true);
    myfont.load("gt-walsheim-bold.ttf",100,true);
    
    //myfont.load("Montserrat-Bold.otf", 300);

    middleX = ofGetWidth()/2;
    middleY = ofGetHeight()/2;
    
    spacing = 300;
    //--------------------
    
//    ofxXmlSettings dataLog;
//    dataLog.setValue("User1:time", 10);
//    dataLog.setValue("User1:color", "blue");
//    dataLog.setValue("User1:day", std::to_string(ofGetDay()));
//    dataLog.setValue("User1:hour", std::to_string(ofGetHours()) + "." + std::to_string(ofGetMinutes()));
//
//    dataLog.saveFile("Log_BlueProject_" + std::to_string(ofGetDay()) + "_"
//                                        + std::to_string(ofGetHours()) + "h"
//                                        + std::to_string(ofGetMinutes()) + ".xml");
//    
    appState = STATE_IDLE;
    
//GPIO----------------------------
//    gpio17.setup("17");
//    gpio17.export_gpio();
//    gpio17.setdir_gpio("in");
//    
//    gpio21.setup("21");
//    gpio21.export_gpio();
//    gpio21.setdir_gpio("in");
    


}

//--------------------------------------------------------------
void ofApp::update(){
    
    //DISPLAYEJAR COMPTADOR-------------------------------------------
    
    if (isCounterOn)
    {
        timer = ofGetElapsedTimef()- counter;
        
        if (timer!= prevTimer)
            digit3+=1;
        if (digit3 == 10)
        {
            digit3 = 0;
            digit2 += 1;
            
            if (digit2 == 6)
            {
                digit2 = 0;
                digit1+=1;
                
            }
        }
        
        prevTimer = ofGetElapsedTimef()-counter;
    }
    
    if (timer == 0)
    {
        digit1 = 0;
        digit2 = 0;
        digit3 = 0;
        prevTimer = 0;
        
    }
    
    
    clock = std::string("0")+std::to_string(digit1)+":"+std::to_string(digit2)+std::to_string(digit3);
    // ---------------------------------------------------------------

    
    switch(appState){
        case STATE_IDLE:
            idle();
            break;
        case STATE_WARMING:
            warming();
            break;
        case STATE_PLAY:
            play();
            break;
        case STATE_POSTPLAY:
            postPlay();
            break;
        case STATE_CRISIS:
            crisis();
            break;
    }
    
    
    
    //gpio17.getval_gpio(state_buttonON);
    
    
    /////////// SERIAL ///////
    //unsigned char lectura[3];
    unsigned char* lectura;
	lectura = new unsigned char(' '); //[2] = {' ', ' '};
    serial.readBytes(lectura, 1);  //int readBytes(unsigned char * buffer, int length);
    
   cout << *lectura << endl;
    
   
    if (*lectura == 'Y'){
        buttonON = true;
        cout << "HE REBUT ON!!!!" << endl;
    }
    else {
        buttonON = false;
    
    }
    
    if (*lectura == 'N'){
        buttonOFF = true;
        cout << "HE REBUT OFF!!!!" << endl;
    }
    else {
        buttonOFF = false;
        
    }
    
//    if (ofToInt(state_buttonON) == 1){
//        buttonON = true;
//        cout << "ON!!" << endl;
//    }
//    else
//        buttonON = false;
//
//    gpio21.getval_gpio(state_button);
//    
//    
//    
//    if (ofToInt(state_button) == 1){
//        buttonOFF = true;
//        cout << "OFF!!" << endl;
//    }
//    else
//        buttonOFF = false;
    
    
    // LIGHT
    Light::getInstance().getInfo();
    
    //cout << appState << endl;
    
}

//--------------------------------------------------------------
void ofApp::idle(){
    if (buttonON) {
        
        counter = ofGetElapsedTimef(); // aquest serˆ el temps d'entrada del nou usuari
        
        isCounterOn = true; // comencem a comptar
        
        userIndex += 1; //aquest serˆ l'index del nou usuari
        
        Light::getInstance().changeColor();
        //Light::getInstance().fadePars(1,'O', 1, 1000, 1); //no hauria de ser warming time!!
        Light::getInstance().fadePars(1, 'I', 0, 1000, 2);     //no hauria de ser warming time!!
        
        appState = STATE_WARMING;
        
    }
    
}

//--------------------------------------------------------------
void ofApp::warming(){
    
    if ((ofGetElapsedTimef() - counter) > warmingTime) {
        appState = STATE_PLAY;
    }
    
    // IMPLEMENT CRISIS
    
}


//--------------------------------------------------------------
void ofApp::play(){
    
    if (buttonOFF || ((ofGetElapsedTimef() - counter) > maxErrorTime) ) {
        
         cout << "button OFF................" << endl;
        
        // SAVE DATA:
        
        finalCounter = ofGetElapsedTimef() - counter; //interval de temps passat quan es para el comptador
        
        saveData();

        isCounterOn = false; //El comptador es queda quiet
        
        postPlayCounter = ofGetElapsedTimef();
        
        appState = STATE_POSTPLAY;
        
        Light::getInstance().fadePars(1, 'O', 1, postPlayTime*500, 3);
        
        //return 0;
        
    }
    
//    if ((ofGetElapsedTimef() - counter) > maxErrorTime) {                // no escrius?
//        // SAVE DATA?
//        appState = STATE_IDLE;
//        
//    }
    
    
}


//--------------------------------------------------------------
void ofApp::postPlay(){
    
    if ((ofGetElapsedTimef() - postPlayCounter) > postPlayTime) {
        appState = STATE_IDLE;
        
        cout << "POST PLAY................" << endl;
        
        // SET counter TO 0!!
        timer = 0;
    }
    
}

//--------------------------------------------------------------
void ofApp::crisis(){
    // IMPLEMENTAR!
    
    
}


void ofApp::saveData()
{
    string userTime = "User" + std::to_string(userIndex) + ":time";
    string userColor = "User" + std::to_string(userIndex) + ":color";
    string userDay = "User" + std::to_string(userIndex) + ":day";
    string userHour = "User" + std::to_string(userIndex) + ":hour";
    
    
    dataLog.setValue(userTime, finalCounter);
    dataLog.setValue(userColor, Light::getInstance().getCurrentColor()); //<<<<<<<-----------------------------!!!!!INTRODUIR COLOR!!!!!
    dataLog.setValue(userDay, std::to_string(ofGetDay()));
    dataLog.setValue(userHour, std::to_string(ofGetHours()) + "." + std::to_string(ofGetMinutes()));
    
    dataLog.saveFile("Log_BlueProject_" + std::to_string(ofGetDay()) + "_"
                     + std::to_string(ofGetHours()) + "h"
                     + std::to_string(ofGetMinutes()) + ".xml");
    
    dataLog.saveFile("Log_BlueProject_" + std::to_string(ofGetDay()) + "_"
                     + std::to_string(ofGetHours()) + "h"
                     + std::to_string(ofGetMinutes()) + "_copy.xml");

}


void ofApp::keyPressed(int key)
{
    switch(key)
    {
        case 'f':
            buttonON = true;
            break;
        case 'j':
            buttonOFF = true;
            break;
    }
    
}

void ofApp::keyReleased(int key)
{
    switch(key)
    {
        case 'f':
            buttonON = false;
            break;
        case 'j':
            buttonOFF = false;
            break;
    }
    
}




//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    
    myfont.drawString(clock, middleX-400,middleY);
    
   // ofDrawBitmapString(appState,10,10);
    
    //ofDrawBitmapString(clock,middleX,middleY,100);
    
   // myfont.drawString("Helena",10,10);

}
