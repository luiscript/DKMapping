/*
 Copyright (C) 2018 Luis Fernando García [http://luiscript.com]
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#ifndef DKMapping_hpp
#define DKMapping_hpp

#include "DKModule.hpp"
#include "DKWireConnection.hpp"
#include "ofxMeshWarp.h"
#include "ofxMeshWarpManagedController.h"


class DKMapping : public DKModule{
private:
    ofFbo * fboInput;
    ofFbo * fboOutput;
    bool drawFbo;
    float scaleX;
    float scaleY;
    std::shared_ptr<ofxMeshWarp> mesh_;
    ofxMeshWarpController controller_;
    ofTexture tex_;
    bool drawMesh;
public:
    void setup();
    void update();
    void draw();
    void setFbo(ofFbo *);
    ofFbo * getFbo();
    void addModuleParameters();
    void onMappingMode(ofxDatGuiToggleEvent);
};


#endif /* DKMapping_hpp */
