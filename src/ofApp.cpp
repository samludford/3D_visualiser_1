/* This is an example of how to integrate maximilain into openFrameworks,
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */

#include "ofApp.h"

// 1. pass audio in to audio out
// 2. use fft to visualise it on the way

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    ofSetFrameRate(60);
    ofBackground(0,0,0);
    ofSetColor(255.0);
    
    // camera setup
    cam.setDistance(1000.0);
    
    ofSetCircleResolution(100);
    
    // audio setup
    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    
    ofSoundStreamListDevices();
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    lAudioOut = new float[bufferSize];
    rAudioOut = new float[bufferSize];
    lAudioIn = new float[bufferSize];
    rAudioIn = new float[bufferSize];
    
    memset(lAudioOut, 0, bufferSize * sizeof(float));
    memset(rAudioOut, 0, bufferSize * sizeof(float));
    memset(lAudioIn, 0, bufferSize * sizeof(float));
    memset(rAudioIn, 0, bufferSize * sizeof(float));
    
    volume = 0.5;
    
    fftSize = 1024;
    fft.setup(fftSize, 512, 256);
    
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    
    ofNoFill();
    
    float xinc = ofGetWidth() / (fftSize * 2.0);
    for(int i=0; i < (fftSize/2.0); i++) {
        float radius = fft.magnitudes[i] * 100;
        ofDrawCircle(0, 0, (i*xinc)*4.0, radius);
    }
    
    cam.end();
    
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){

        wave = lAudioIn[i];
        
        if(fft.process(wave)) {
            fft.magsToDB();
        }
        
        mix.stereo(wave, outputs, 0.5);
        
        output[i*nChannels    ] = outputs[0] * volume;
        output[i*nChannels + 1] = outputs[1] * volume;

    }
    
    
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    float sum = 0;
    for(int i = 0; i < bufferSize; i++){
        lAudioIn[i] = input[i*2];
        rAudioIn[i] = input[i*2+1];
        sum += input[i*2] * input[i*2];
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        ofSaveScreen(ofToString(ofGetFrameNum()) + ".png");
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
    
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
