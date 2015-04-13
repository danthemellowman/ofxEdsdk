#include "testApp.h"

void testApp::setup() {
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    bIsRecordingMovie = false;
    camera.setup();
    timer.setFramerate(10);
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
        textures = camera.getPhotoTextures();
//        pixels = camera.getPhotoPixels();
//        if(pixels.size() == 10){
//            string dir = ofGetTimestampString();
//            ofDirectory::createDirectory(dir);
//            for(int i = 0; i < pixels.size(); i++){
//                ofSaveImage(pixels[i], dir+"/"+ofToString(i)+".png");
//            }
//            pixels.clear();
//        }
    }

    if(camera.isMovieNew()) {
        camera.savePhoto(ofToString(ofGetFrameNum()) + ".mov");
    }
}

void testApp::draw() {
    camera.draw(0, 0, camera.getWidth()/2, camera.getHeight()/2);
    camera.drawPhoto(0, camera.getHeight()/2);
    
    if(textures.size() > 0){
        textures[mIndex].draw(camera.getWidth()/2, 0);
        if(timer.tick())
            mIndex= (mIndex+1)%textures.size();
    }
    
    //if(camera.isLiveDataReady()) {
    stringstream status;
    status << camera.getWidth() << "x" << camera.getHeight() << " @ " <<
    (int) ofGetFrameRate() << " app-fps / " <<
    (int) camera.getFrameRate() << " cam-fps / " <<
    (camera.getBandwidth() / (1<<20)) << " MiB/s";
    ofDrawBitmapString(status.str(), 10, 20);
    //}
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