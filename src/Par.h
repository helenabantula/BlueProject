//
//  par.h
//  Corasonsitu
//
//  Created by Helena Bantulà i Fonts on 27/11/15.
//
//

#ifndef __Corasonsitu__par__
#define __Corasonsitu__par__

#include <iostream>
#include "ofxArtnet.h"
#include "ofMain.h"

#endif

class Par {

public:
    

    // FEATURES
    
    ofColor color;
    ofColor colorI;            //color inicial, sempre el mateix
    int id;

    
    // FADES

    int stepFI = 200; //in milliseconds
    int stepFO = 200;
    bool isFadeIn = false;
    bool isFadeOut = false;
    float topFade = 0.3;
    int type=1;


    // OTHERS
    
    int i;
    bool isRandom = false;
    int time;
    
    
    
    Par (ofColor,int);
    void fadeIn();
    void triggerFadeIn(int tipus, int step);
    void triggerFadeOut(int step);
    void fadeOut();
    void update();
    void randomMove();
    
    ofColor getColor(){return color;};
    
    void multiplyColor(int k){color = colorI*k;};
    void setColor(ofColor newColor){
        color = newColor;
        colorI = newColor;
    };

    
};
