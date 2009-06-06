#ifndef _HouseOfPhthah_
#define _HouseOfPhthah_

#include <Ogre.h>
#include "ExampleFrameListener.h"

class CHouseOfPhthah
{
public :
	CHouseOfPhthah();
	~CHouseOfPhthah();
	
	void Start();
	void Run();
	void Exit();
	
public :
	Ogre::Root*				mRoot;
	Ogre::SceneManager*		mSceneMgr;
	Ogre::Viewport*			mViewport;
	Ogre::Camera*			mCamera;
    Ogre::RenderWindow*		mWindow;
	Ogre::String			mResourcePath;
	ExampleFrameListener*	mFrameListener;

private:
	void		configure();
	void		chooseSceneManager();
	void		createCamera();
	void		createScene();
	void		destroyScene();
	void		createViewports();
	void		setupResources();
	void		loadResources();
	void		createResourceListener();
	void		createFrameListener();
};

#endif //_HouseOfPhthah_