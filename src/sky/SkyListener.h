#ifndef _SkyListener_
#define _SkyListener_

#include <Caelum.h>
#include <OgreFrameListener.h>
#include <OgreString.h>

using namespace Ogre;

class CSky;

class CSkyListener: public Ogre::FrameListener
{
public:
	CSkyListener(CSky* Sky, Camera* camera = NULL, SceneNode* skyDomeNode = NULL);
	virtual ~CSkyListener();
	bool frameStarted(const Ogre::FrameEvent& evt);
private:
	CSky* mSky;
	Camera* mCamera;
	SceneNode* mSkyDomeNode;
};

#endif // _SkyListener_