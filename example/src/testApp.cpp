#include "testApp.h"

void testApp::setup() {
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    bIsRecordingMovie = false;
    camera.setup();
}

void testApp::exit() {
    camera.close();
}

void testApp::update() {
    camera.update();
    if(camera.isFrameNew()) {
        // process the live view with camera.getLivePixels()
    }
    
    if(camera.isPhotoNew()) {
        // process the photo with camera.getPhotoPixels()
        // or just save the photo to disk (jpg only):
        textures = camera.getPhotoTexture();
        pixels = camera.getPhotoPixels();
        string dir = ofGetTimestampString();
        ofDirectory::createDirectory(dir);
        for(int i = 0; i < pixels.size(); i++){
            ofSaveImage(pixels[i], dir+"/"+ofToString(i)+".png");
        }
//        textures.push_back(tex);
//        camera.savePhoto(ofToString(ofGetFrameNum()) + ".png");
    }
    
    if(camera.isMovieNew()) {
        camera.savePhoto(ofToString(ofGetFrameNum()) + ".mov");
    }
}

void testApp::draw() {
    camera.draw(0, 0, camera.getWidth()/2, camera.getHeight()/2);
    
    for(int i = 0; i < textures.size(); i++){
        textures[i].draw(camera.getWidth()/2+textures[i].getWidth()/10*i, 0, textures[i].getWidth()/10, textures[i].getHeight()/10);
    }
    
    if(camera.isLiveDataReady()) {
        stringstream status;
        status << camera.getWidth() << "x" << camera.getHeight() << " @ " <<
        (int) ofGetFrameRate() << " app-fps / " <<
        (int) camera.getFrameRate() << " cam-fps / " <<
        (camera.getBandwidth() / (1<<20)) << " MiB/s";
        ofDrawBitmapString(status.str(), 10, 20);
    }
}

void testApp::keyPressed(int key) {
    if(key == ' ') {
        camera.takePhoto();
    }
    if(key == 's') {
        camera.setup();
    }
    if(key == 'c') {
        camera.close();
    }
    else if(key == 'v') {
        bIsRecordingMovie ^= true;
        if (bIsRecordingMovie) {
            camera.beginMovieRecording();
        } else {
            camera.endMovieRecording();
        }
    }
    
}