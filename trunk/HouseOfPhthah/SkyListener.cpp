#include "SkyListener.h"
#include "Sky.h"

#include <Caelum.h>
#include <OgreEntity.h>
#include <OgreMaterialManager.h> 
#include <OgreRoot.h>

#include "Macros.h"

CSkyListener::CSkyListener(CSky* sky, Camera* camera, SceneNode* skyDomeNode):
	mSky(sky),
	mCamera(camera),
	mSkyDomeNode(skyDomeNode)
{
}

CSkyListener::~CSkyListener()
{
	// I don't want to delete these things since CSky can handle it
	mCamera = NULL;
	mSkyDomeNode = NULL;
	mSky = NULL;
}

bool  CSkyListener::frameStarted(const Ogre::FrameEvent& evt)
{
	switch ( mSky->getSkyType() )
	{
	case CSky::PHTHAH_SKY_DOME:
		{
			assert(mCamera&&mSkyDomeNode&&"Problem in CSkyListener::frameStarted()");
			// position the skydome at camera position as frequently as possible (I should assert that SkyDomeNode exists)
			// trick to make the sky closer to the camera, thus player can't easily see the void under the terrain unless he's very close to the border
			mSkyDomeNode->setPosition(mCamera->getPosition() - Ogre::Vector3(0,50,0));
		}
	break;
	case CSky::CAELUM_SKY_DOME:
		{
			Caelum::CaelumSystem* caelumSystem = mSky->getCaelumSystem();
			assert(mCamera&&caelumSystem&&"Problem in CSkyListener::frameStarted()");
			caelumSystem->notifyCameraChanged(mCamera);
			// we make the sky evolve with time (if activated, problem with OGRE_SKY_DOME; if deactivated, no sun nor moon in OGRE_SKY_DOME)
			caelumSystem->updateSubcomponents(evt.timeSinceLastFrame);
		}
	break;
	default:
	break;
	}

	return true;
}