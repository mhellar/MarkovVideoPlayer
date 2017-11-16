#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(false);
	ofSetFrameRate(60);
    
    //setup our directory
    dir.setup();
    //setup our client
    client.setup();
    
    //register for our directory's callbacks
    ofAddListener(dir.events.serverAnnounced, this, &ofApp::serverAnnounced);
    // not yet implemented
    //ofAddListener(dir.events.serverUpdated, this, &ofApp::serverUpdated);
    ofAddListener(dir.events.serverRetired, this, &ofApp::serverRetired);
    
    dirIdx = -1;
	ofxMC::Matrix mat("transitionMatrix.txt");
	markov.setup(mat, 0);

	gui.setup("Settings");
	gui.add(cycle.set("Cycle", 15, 0, 90));
	gui.add(fps.setup("Fps:", ""));
    vid1.load("1.mp4");

    
    vid1.setLoopState(OF_LOOP_NONE);


}

//these are our directory's callbacks
void ofApp::serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Announced")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}

void ofApp::serverUpdated(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Updated")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}

void ofApp::serverRetired(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Retired")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}


//--------------------------------------------------------------
void ofApp::update(){
    markov.update();
    if(++i > cycle){

        i = 0;
        
    }
    vid1.update();
    if(vid1.getIsMovieDone() == 1){
        markovNext();
    }



}

//--------------------------------------------------------------
void ofApp::draw(){

    if(dir.isValidIndex(dirIdx))
        client.draw(0, 0);
    vid1.draw(0,0);
    vid1.play();
}



void ofApp::keyPressed  (int key){
    switch(key){
        case 'f':
            markovNext();
        case 'l':
            //press any key to move through all available Syphon servers
            if (dir.size() > 0)
            {
                dirIdx++;
                if(dirIdx > dir.size() - 1)
                    dirIdx = 0;
                
                client.set(dir.getDescription(dirIdx));
                string serverName = client.getServerName();
                string appName = client.getApplicationName();
                
                if(serverName == ""){
                    serverName = "null";
                }
                if(appName == ""){
                    appName = "null";
                }
                ofSetWindowTitle(serverName + ":" + appName);
            }
            else
            {
                ofSetWindowTitle("No Server");
            }
    }
}

void ofApp::markovNext(){
    if(markov.getState() != 0){
        n = markov.getState();
        cout << n;
        j = markov.getState();
        if(j == 0){
            vid1.loadAsync("1.mp4");
        }
        else if(j == 1){
            vid1.loadAsync("2.mp4");
        }
        else if(j == 2){
            vid1.loadAsync("3.mp4");
        }
        else if(j == 3){
            vid1.loadAsync("4.mp4");
        }
        else if(j == 4){
            vid1.loadAsync("5.mp4");
            
        }
        else if(j == 5){
            vid1.loadAsync("6.mp4");
        }
        else if(j == 6){
            vid1.loadAsync("7.mp4");
        }
        else if(j == 7){
            vid1.loadAsync("8.mp4");
        }
        else if(j == 8){
            vid1.loadAsync("9.mp4");
        }
        else if(j == 9){
            vid1.loadAsync("10.mp4");
        }

        
    }
}

