#ifndef _HouseOfPhthah_
#define _HouseOfPhthah_

#include <Ogre.h>
#include "ExampleFrameListener.h"
#include "SkyDome.h"
#include "Terrain.h"

class CHouseOfPhthah : public Ogre::Singleton< CHouseOfPhthah >
{
public :
	CHouseOfPhthah();
	~CHouseOfPhthah();

	static CHouseOfPhthah& getSingleton(void);
    static CHouseOfPhthah* getSingletonPtr(void);

	
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

private:
	CSkyDome	mSkyDome;
	CTerrain	mTerrain;
};

#endif //_HouseOfPhthah_