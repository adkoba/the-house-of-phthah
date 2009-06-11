#ifndef _Water_
#define _Water_

#include <OgreFrameListener.h>
#include <OgreMaterial.h> 
#include <OgreRenderTargetListener.h> 
#include <OgreString.h>
#include <OgreTexture.h> 

using namespace Ogre;

class Ogre::Camera;
class Ogre::Entity;
class Ogre::MovablePlane;
class Ogre::SceneNode;

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
    bool frameRenderingQueued(const FrameEvent& evt);
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