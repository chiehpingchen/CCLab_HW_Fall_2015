#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    ofBackground(0,0,0);
	
	camWidth 		= 640;	// try to grab at this size. 
	camHeight 		= 480;
	
	vidGrabber.setVerbose(true);
	vidGrabber.setup(camWidth,camHeight);


	font.load("Courier New Bold.ttf",3);
    
    // this set of characters comes from processing: 
    //http://processing.org/learning/library/asciivideo.html
    
	// changed order slightly to work better for mapping
    asciiCharacters =  string("  ..,,,'''``--_:;^^**""=+<>iv%&xclrs)/){}I?!][1taeo7zjLunT#@JCwfy325Fp6mqSghVd4EgXPGZbYkOA8U$KHDBWNMR0Q");
	
    ofEnableAlphaBlending();
}


//--------------------------------------------------------------
void ofApp::update(){
	vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	
    
    
    // change background video alpha value based on the mouse position
    float videoAlphaValue = ofMap(mouseX, 0,ofGetWidth(),100,255);
    
    // set a white fill color with the alpha generated above
    ofSetColor(255,255,255,videoAlphaValue);
    
    
    float typeValue = ofMap(mouseY, 0,ofGetHeight(),9,72);
    
    font.load("Courier New Bold.ttf",typeValue);

    // draw the raw video frame with the alpha value generated above
    vidGrabber.draw(0,0);

	ofPixelsRef pixelsRef = vidGrabber.getPixels();
    
    ofSetHexColor(0xffffff);

    for (int i = 0; i < camWidth; i+= 7){
        for (int j = 0; j < camHeight; j+= 9){
            // get the pixel and its lightness (lightness is the average of its RGB values)
            float lightness = pixelsRef.getColor(i,j).getLightness();
            // calculate the index of the character from our asciiCharacters array
            int character = powf( ofMap(lightness, 0, 255, 0, 1), 2.5) * asciiCharacters.size();
            // draw the character at the correct location
            font.drawString(ofToString(asciiCharacters[character]), i, j);
        }
    }
 
    

    ofTranslate(ofGetWidth()/2,ofGetHeight()/2); // move initital drawing postion to the center of the screen
    
    
    
    //    int circle_resolution=1600;
    // amount of points circle is made of, more points - better quality, but could decrease perfomance
    
    
    float cResolution = ofMap(mouseY, 0,ofGetHeight(),1800,180);
    
    int circle_resolution=cResolution;
    
    
    
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
    ofSetColor(clr,30);
    circle_sin.close(); // to connect first and last point of our shape we need to use ÔcloseÕ function
    circle_sin= circle_sin.getSmoothed(1);
    circle_sin.draw();
    
    clr=ofColor::fromHex(0x000000);
    ofSetColor(clr,30);
    circle_cos.close();
    circle_cos= circle_cos.getSmoothed(1);
    circle_cos.draw();
    
    
    clr=ofColor::fromHex(0xff0000);
    ofSetColor(clr,30);
    circle_un_cos.close();
    circle_un_cos= circle_un_cos.getSmoothed(1);
    circle_un_cos.draw();

    
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}
	
	
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
