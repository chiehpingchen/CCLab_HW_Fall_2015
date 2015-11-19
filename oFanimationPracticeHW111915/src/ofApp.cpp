#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw()
{

    
    
    ofBackground(0);// draw grey background
    ofSetColor(255);// set color drawing color to white
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2); // move initital drawing postion to the center of the screen
    
    
    
//    int circle_resolution=1600;
    // amount of points circle is made of, more points - better quality, but could decrease perfomance
    int circle_resolution=1800;
    
    
    
//    int radius=200; // radius of the circle
    int radius=450;
    
    
    
//    int smoothing_amount=10;
    int smoothing_amount=0.1;
    
    ofPolyline circle_sin;
    ofPolyline circle_cos;
    ofPolyline circle_un_cos;
    
    
//    int wave_height=radius*0.1; // height of sine waves
    int wave_height=radius;
    
    
    
//    int anim_shape=16; // amount waves per circle
    int anim_shape=3000;
    
    
    
//    float sine_pct=0.5; // how long is wave in percantage
    float sine_pct=8;
    

    
    float speed_increment=ofGetElapsedTimef()*0.5; // speed of animation

    
    
    
    
//    int line_w=7; // width of the stroke
    int line_w=0.01;
    
    
    
    int radius_cos=radius+line_w-1; // let's make it little less then line width, so circles will overlap each other
    int radius_un_cos=radius+(line_w-1)*2;
    for(int i=0; i<circle_resolution; i++)
    {
        
        float angle=TWO_PI/circle_resolution*i;
        float raidus_addon=wave_height*sin((angle+speed_increment)*anim_shape);
        
        float x=cos(angle+speed_increment)*radius;
        float y=sin(angle+speed_increment)*radius;
        
        // drawing sine wave only on a part of the circle
        if(i<sine_pct*circle_resolution)
        {
            x=cos(angle+speed_increment)*(radius+raidus_addon);
            y=sin(angle+speed_increment)*(radius+raidus_addon);
        }
        circle_sin.addVertex(ofPoint(x,y));
        
        
        raidus_addon=wave_height*cos((angle+speed_increment)*anim_shape);
        x=cos(angle+speed_increment)*(radius_cos);
        y=sin(angle+speed_increment)*(radius_cos);
        
        if(i<sine_pct*circle_resolution)
        {
            x=cos(angle+speed_increment)*(radius_cos+raidus_addon);
            y=sin(angle+speed_increment)*(radius_cos+raidus_addon);
        }
        
        circle_cos.addVertex(ofPoint(x,y));
        
        
        //increment a wave angle to flip the wave
        raidus_addon=wave_height*cos((angle+TWO_PI/3+speed_increment)*anim_shape);
        x=cos(angle+speed_increment)*(radius_un_cos);
        y=sin(angle+speed_increment)*(radius_un_cos);
        
        if(i<sine_pct*circle_resolution)
        {
            x=cos(angle+speed_increment)*(radius_un_cos+raidus_addon);
            y=sin(angle+speed_increment)*(radius_un_cos+raidus_addon);
        }
        
        circle_un_cos.addVertex(ofPoint(x,y));
        
        
    }
    
    ofSetLineWidth(line_w);
    
    ofColor clr=ofColor::fromHex(0xfff400);
    ofSetColor(clr);
    circle_sin.close(); // to connect first and last point of our shape we need to use ÔcloseÕ function
    circle_sin= circle_sin.getSmoothed(1);
    circle_sin.draw();
    
    clr=ofColor::fromHex(0x000000);
    ofSetColor(clr);
    circle_cos.close();
    circle_cos= circle_cos.getSmoothed(1);
    circle_cos.draw();
    
    
    clr=ofColor::fromHex(0xff0000);
    ofSetColor(clr);
    circle_un_cos.close();
    circle_un_cos= circle_un_cos.getSmoothed(1);
    circle_un_cos.draw();
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
