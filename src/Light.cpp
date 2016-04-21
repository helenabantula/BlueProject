//  light.cpp
//  Corasonsitu
//
//  Created by Helena Bantulà i Fonts on 17/11/15.
//
//

#include "Light.h"


void Light::initialize(){
#if TARGET_RASPBERRY_PI
    artnet.setup("192.168.1.128"); //IP de rPi
#else
    artnet.setup("192.168.1.102"); //IP ordinador
#endif    
 
    ofColor  color(255,0,0);
    colors.push_back(color);
    
    color.set(0, 0, 255);
    colors.push_back(color);

    
    for (int i = 0; i < maxPar; i++){
        Par temPar(colors[0],i);            //inicialitza amb qualsevol color!
        pars.push_back(temPar);
    }
    
    idxButtonPars[0] = 0;
    idxButtonPars[1] = 1;
    

    vector<unsigned char> tempPackDMX(maxPar*3);
    packDMX = tempPackDMX;
    
    this->getInfo();
}



void Light::getInfo(){
    
    int j = 0;
    for (int i = 0; i < maxPar; i++){
        
        pars[i].update();
        
        packDMX[j] = pars[i].getColor().r;
        packDMX[j+1] = pars[i].getColor().g;
        packDMX[j+2] = pars[i].getColor().b;
        j = j+3;
    }
    
    this->sendInfo();
}


void Light::sendInfo(){
    
    artnet.sendDmx("192.168.1.151",&packDMX[0], packDMX.size());
}


void Light::fadePars(float topFade, char fadeType, int FItype, int fadeTime, int howMany){
    

    if (howMany == 2){
        
        for (int i = 0; i < maxPar; i++){
            
            pars[i].topFade = topFade;
            
            if (fadeType == 'I'){
                pars[i].triggerFadeIn(FItype, fadeTime);
            }
            else if (fadeType == 'O') {
                pars[i].triggerFadeOut(fadeTime);
            }
        }
    
    }
    
    else if (howMany == 1){
        
        
        for (int i = 0; i < sizeof(idxButtonPars); i++){
        
            int idx = idxButtonPars[i];
        
            pars[idx].topFade = topFade;
        
            if (fadeType == 'I'){
                    pars[idx].triggerFadeIn(FItype, fadeTime);
                }
            else if (fadeType == 'O') {
                    pars[idx].triggerFadeOut(fadeTime);
                }
                
            }
    
    }
    
    else if (howMany == 3){
        
        // CONSTRUCCIO VECTORS
        //vector<int> idxNoButtonPars(maxPar - sizeof(idxButtonPars));
        vector<int> idxNoButtonPars(maxPar - 2);  // non-user indexs
        
        int j = 0;
        for (int i = 0; i < maxPar; i++){
            if ((i != idxButtonPars[0]) && (i != idxButtonPars[1])) {
                idxNoButtonPars[j] = i;
                j++;
            }
        }
        
        for (int i = 0; i < idxNoButtonPars.size(); i++){
            
            int idx = idxNoButtonPars[i];
            
            pars[idx].topFade = topFade;
            
            if (fadeType == 'I'){
                pars[idx].triggerFadeIn(FItype, fadeTime);
            }
            else if (fadeType == 'O') {
                pars[idx].triggerFadeOut(fadeTime);
            }
            
        }
    }

}



void Light::changeColor(){
    
    
    float randIdx = ofRandomf();
    int idx;
    
    if (randIdx > 0)
    {
        idx = 1;
        currentColor = "blue";
    
    } else
    {
        idx = 0;
        currentColor = "red";
    }
    
    this->setParsColor(colors[idx]);
    

}


void Light::setParsColor(ofColor color){
    
    for (int i = 0; i < maxPar; i++){
        pars[i].setColor(color);
    }
    
}



void Light::setParState(float topColor){
    
    for (int i = 0; i < maxPar; i++){
        pars[i].setColor(topColor);
        
    }
    
}

string Light::getCurrentColor()
{
    return currentColor;
}



void Light::randomPlay(bool state){

    for (int i=0; i<maxPar; i++){
        pars[i].isRandom = state;
    }
}


