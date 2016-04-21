//
//  Light.h
//  Corasonsitu
//
//  Created by Helena Bantulà i Fonts on 17/11/15.
//
//

#ifndef __Corasonsitu__light__
#define __Corasonsitu__light__

#include <iostream>
#include "ofxArtnet.h"
#include "Par.h"



class Light{
    
public:
    
    static Light &getInstance()
    {
        static Light instance;
        return instance;
        
    }
    
    
    // ARTNET & DMX
    ofxArtnet artnet;
    vector<unsigned char> packDMX;
    
    
    // PARS & COLORS
    vector<ofColor> colors;
    vector<Par> pars;
    int idxButtonPars[2];
    
    string currentColor;
    
    int maxPar = 6;
  
    
    void initialize();
    void changeColor();
    
    void getInfo();
    void sendInfo();
    
    void fadePars(float topFade, char fadeType, int FItype, int fadeTime, int howMany); //tots els pars
    void fadeButtonPars(float topFade, char fadeType, int FItype, int fadeTime); //uns quants pars
    void switchColor(ofColor color);
    
    
    void setParsColor(ofColor color);
    void setParState(float topColor);
    
    
    string getCurrentColor();
    
    void randomPlay(bool state);


    
};

#endif /* defined(__Corasonsitu__light__) */