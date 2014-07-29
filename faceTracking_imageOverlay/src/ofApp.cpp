#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	finder.setup("haarcascade_frontalface_default.xml");
    webcam.initGrabber( 1280 , 800 ) ;
    scaledSize = ofRectangle( 0 , 0 , webcam.getWidth() / 4 , webcam.getHeight() / 4 ) ;
    
    faceImage.loadImage( "face.png" ) ; 
}

//--------------------------------------------------------------
void ofApp::update(){
    webcam.update() ;
    
    if ( webcam.isFrameNew() )
    {
        //comment out the above and use the following instead
        //We make a copy of the pixels from the webcam
        ofPixels pix ;
        pix.setFromPixels( webcam.getPixels() , webcam.getWidth() , webcam.getHeight() , 3 ) ; 

        //resizing the pixels to a smaller array will improve performance
        pix.resize( scaledSize.getWidth() , scaledSize.getHeight() ) ;
        finder.findHaarObjects( pix ) ; 
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //Setting the color to white set images to draw at full color
    ofSetColor( ofColor::white ) ;
    webcam.draw( 0, 0 ) ; 
	
    ofNoFill();
    
	for(unsigned int i = 0; i < finder.blobs.size(); i++)
    {
        //Use a stringstream object to generate a label
        stringstream label ;
        label << "face #" << i ;
        
        //Get the rectangle from the haarFinder
		ofRectangle cur = finder.blobs[i].boundingRect;
        
        //because we have a scaled image, we need to adjust the coordinate space of the haar finder rectangle
        float scaleToWebcam = webcam.getWidth() / scaledSize.getWidth() ;
        cur.scale( scaleToWebcam ) ;
        cur.x *= scaleToWebcam ;
        cur.y *= scaleToWebcam ;
        
        //Draw a face starting in the top left
        ofSetColor( ofColor::white ) ;
        faceImage.draw( cur.x , cur.y , cur.getWidth() , cur.getHeight() ) ; 
        
    }

    
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
