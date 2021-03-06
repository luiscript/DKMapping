/*
 Copyright (C) 2018 Luis Fernando Garc�a [http://luiscript.com]
 
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

#include "DKMapping.hpp"
#include "ofxMeshWarpIO.h"
using namespace std;

void DKMapping::setup()
{
    drawFbo = drawMesh = false;
    fboOutput = fboInput = nullptr;
    scaleX = scaleY = 0.25;
    addInputConnection(DKConnectionType::DK_FBO);
    addOutputConnection(DKConnectionType::DK_FBO);
}

void DKMapping::update()
{
    if (drawFbo) {
        tex_ = fboInput->getTexture();
        mesh_->update();
        
        fboOutput->begin();
        ofClear(0,0,0);
        tex_.bind();
        mesh_->drawMesh();
        tex_.unbind();
        fboOutput->end();   
    }
}

void DKMapping::draw()
{
    if(drawFbo)
    {
        ofPushMatrix();
        ofTranslate(gui->getPosition().x, gui->getPosition().y + 70);
        ofScale(scaleX, scaleY);
        fboOutput->draw(0,0);
        ofPopMatrix();
        
        if(drawMesh)
        {
            controller_.setScale(scaleX);
			controller_.setTranslationGui(getTranslation().x, getTranslation().y);
            controller_.setTranslation(gui->getPosition().x + getTranslation().x, gui->getPosition().y  + getTranslation().y + 70);
            controller_.draw();
        }
    }
    
}

void DKMapping::setFbo(ofFbo * fboPtr)
{
    fboInput = fboPtr;
    if(fboPtr != nullptr)
    {
        fboOutput = new ofFbo;
        fboOutput->allocate(fboInput->getWidth(), fboInput->getWidth(), GL_RGBA);
        fboOutput->begin();
        ofClear(0, 0, 0);
        fboOutput->end();
       
        setModuleWidth(fboInput->getWidth()/4);
        gui->setWidth(fboInput->getWidth()/2);
        
        tex_ = fboInput->getTexture();
        mesh_ = make_shared<ofxMeshWarp>();
    
        mesh_->setup(ofRectangle(2,2,fboInput->getWidth(),fboInput->getHeight()), 2, 2);
        mesh_->setUVRect(ofRectangle(0,0, tex_.getWidth(), tex_.getHeight()));
        controller_.add(mesh_);
        controller_.disable();
        
        drawFbo = true;
    } else
    {
        drawFbo = false;
    }
    
    scaleX = 0.5;
    scaleY = 0.5;
}

ofFbo * DKMapping::getFbo()
{
    return fboOutput;
}


void DKMapping::addModuleParameters()
{
    gui->addToggle("SHOW MESH CONTROLLER")->onToggleEvent(this, &DKMapping::onMappingMode);
}

void DKMapping::onMappingMode(ofxDatGuiToggleEvent e)
{
    drawMesh = e.target->getChecked();
    drawMesh ? controller_.enable() : controller_.disable();
}
