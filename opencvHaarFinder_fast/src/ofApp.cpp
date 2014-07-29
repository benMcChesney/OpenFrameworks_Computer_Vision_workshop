#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	finder.setup("haarcascade_frontalface_default.xml");
    webcam.initGrabber( 640 , 480 ) ;
    
    //Step 2
    scaledSize = ofRectangle( 0 , 0 , webcam.getWidth() / 4 , webcam.getHeight() / 4 ) ;
}

//--------------------------------------------------------------
void ofApp::update(){
    webcam.update() ;
    
    if ( webcam.isFrameNew() )
    {
        //Step 1
        //finder.findHaarObjects( webcam.getPixelsRef() );
        
        //Step 2
        //comment out the above and use the following instead
        //We make a copy of the pixels from the webcam
        ofPixels pix ;
        pix.setFromPixels( webcam.getPixels() , webcam.getWidth() , webcam.getHeight() , 3 ) ; 

        //resizing the pixels to a smaller array will improve performance
        pix.resize( scaledSize.getWidth() , scaledSize.getHeight() ) ;
        finder.findHaarObjects( pix ) ; 
        
    }
    
    //Step 3 - limit the max number of points so there is a "tail"
    if ( polyline.getVertices().size() > 100 )
    {
        polyline.getVertices().erase( polyline.getVertices().begin() ) ;
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
        
        //Step 1 - Get the rectangle from the haarFinder
		ofRectangle cur = finder.blobs[i].boundingRect;
        
        //Step 2 - because we have a scaled image, we need to adjust the coordinate space of the haar finder rectangle
        float scaleToWebcam = webcam.getWidth() / scaledSize.getWidth() ;
        cur.scale( scaleToWebcam ) ;
        cur.x *= scaleToWebcam ;
        cur.y *= scaleToWebcam ;
        
        //Step 3 - add a new vertex to the polyline
        polyline.addVertex( cur.getCenter() ) ;
        
        //Quick and easy way to draw bitmap text in OF
        ofDrawBitmapStringHighlight( label.str() , cur.x , cur.y - 15 ) ;
        ofRect(cur.x, cur.y, cur.width, cur.height);
	}
    
    //Step 3 - draw the raw polyline in red
    ofSetColor( ofColor::red ) ;
    polyline.draw( ) ;
    
    //Draw the smoothed polyline green
    ofSetColor( ofColor::green ) ;
    //Smoothing adds more of a bezier curves for a nicer line
    ofPolyline smoothedPolyline = polyline.getSmoothed( 12 ) ;
    smoothedPolyline.draw( ) ;
    
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
