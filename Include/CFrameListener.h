#ifndef _HOP_FRAME_LISTENER_
#define _HOP_FRAME_LISTENER_


#include <OgreFrameListener.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>

//class Ogre::Camera;
//class Ogre::SceneManager;

class CFrameListener : public Ogre::FrameListener
{
	protected:
		Ogre::Camera*		mOgreCam;
		Ogre::SceneManager*	mOgreSceneMgr;

	public:
		/**
		 * \Brief Default constructor
		 */
		CFrameListener()
			: mOgreCam(NULL)
			, mOgreSceneMgr(NULL)
		{}

		/**
		 * \Brief Default constructor
		 */
		CFrameListener( Ogre::Camera* pCamera, Ogre::SceneManager*	pSceneMgr )
			: mOgreCam(pCamera)
			, mOgreSceneMgr(pSceneMgr)
		{}
};
#endif