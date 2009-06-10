#ifndef _Water_
#define _Water_

#include "Ogre.h"

using namespace Ogre;

class RenderToTextureFrameListener : public FrameListener
{
protected:
	Camera* mCamera;
	Camera* mReflectCam;
    SceneNode* mPlaneNode;
public:
	RenderToTextureFrameListener(Camera* maincam, Camera* reflectCam, SceneNode* planeSceneNode) :
        	mCamera(maincam), 
			mReflectCam(reflectCam), 
			mPlaneNode(planeSceneNode)
    {

    }
    bool frameRenderingQueued(const FrameEvent& evt)
    {
        if( FrameListener::frameRenderingQueued(evt) == false )
		return false;

        // Make sure reflection camera is updated too
        mReflectCam->setOrientation(mCamera->getOrientation());
        mReflectCam->setPosition(mCamera->getPosition());

        // Rotate plane
        //mPlaneNode->yaw(Degree(30 * evt.timeSinceLastFrame), Node::TS_PARENT);

        return true;
    }
};


class CWater : public Ogre::RenderTargetListener
{
public:
	CWater();
	~CWater();

	void init();

protected:
	void createFrameListener(void);

private:
	MaterialPtr		mMat;
	TexturePtr		mReflectionTex;	
	Camera*			mReflectCam;
	
	MovablePlane*	mPlane;
	Entity*			mPlaneEnt;
    SceneNode*		mPlaneNode;
	RenderToTextureFrameListener*	mFrameListener;

};

#endif // _Water_