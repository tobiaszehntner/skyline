#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    numPixels = 210;
    
    minTime = 0;
    maxTime = 14400;
    
    minRGBvalue = 2;
    maxRGBvalue = 255;

    
    ofDirectory dir("keyframes");
    dir.allowExt("jpg");

    int num = dir.listDir();
    
    for (int i = 0; i < num; i++)
    {
        KeyFrame keyFrame;
        
        keyFrame.timestamp = ofToInt(dir[i].getBaseName()); // extract the timestamp from the filename
        
        bool result = keyFrame.pixels.loadImage(dir[i].path());
        
        keyFrame.pixels.resize(1, numPixels);
        
        if (result)
        {
            keyFrames.push_back(keyFrame);
        }
        else
        {
            ofLogError() << "Could not load pixels";
        }
    }
    
    cout << "#define NUM_LEDS " << numPixels << endl << "#define NUM_KEYS " << keyFrames.size() << endl << endl;
    
    cout << "PROGMEM prog_uchar RGB_ARRAY [" << keyFrames.size() << "] [" << numPixels * 3 << "] = { " << endl;
    
    for (int i = 0; i < keyFrames.size(); i++)
    {
        cout << "\t{ ";
        unsigned char* pixels = keyFrames[i].pixels.getPixels();
        
        for (int j = 0; j < keyFrames[i].pixels.getHeight() * 3; j+=3)
        {
            int r = ofMap((int)pixels[j], 0, 255, minRGBvalue, maxRGBvalue);
            int g = ofMap((int)pixels[j+1], 0, 255, minRGBvalue, maxRGBvalue);
            int b = ofMap((int)pixels[j+2], 0, 255, minRGBvalue, maxRGBvalue);
            
//            char rgbValues [17] = {0, 1, 2, 3, 4, 6, 8, 12, 16, 23, 32, 45, 64, 90, 128, 180, 255};
//            
//            int conversionR = ofMap(r , 0, 255, 0, 17);
//            int conversionG = ofMap(g , 0, 255, 0, 17);
//            int conversionB = ofMap(b , 0, 255, 0, 17);
//            
//            r =  r / 255 * rgbValues[conversionR];
//            g =  g / 255 * rgbValues[conversionG];
//            b =  b / 255 * rgbValues[conversionB];
            
            
            
            cout << r << ", " << g << ", " << b;
            
            
            if ( j < numPixels * 3 - 3)
            {
                cout << ", ";
            }
            
        
        }
        
        
        cout << " }";
        
        if ( i < keyFrames.size() - 1)
        {
            cout << ", ";
        }
        
        cout << endl;
    }

    cout << "};" << endl << endl;

    
    cout << "int TIMESTAMPS_ARRAY [" << keyFrames.size() << "] = { ";

    for (int i = 0; i < keyFrames.size(); i++)
    {
        cout << keyFrames[i].timestamp;
        
        if ( i < keyFrames.size() - 1)
        {
            cout << ", ";
        }
        
    }

    cout << " };" << endl;

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

    ofBackground(255);
    
    for (int i = 0; i < keyFrames.size(); i++)
    {
        int x = ofMap(keyFrames[i].timestamp, 0, 1440, 0, ofGetWidth());
        keyFrames[i].pixels.draw(x, 0);
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
