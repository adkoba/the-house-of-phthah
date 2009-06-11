#ifndef _HouseOfPhthah_
#define _HouseOfPhthah_

#include <OgreSingleton.h>
#include <OgreString.h>
#include "Macros.h"
#include "SkyDome.h"
#include "Terrain.h"
#include "Water.h"

class Ogre::Root;
class Ogre::SceneManager;
class Ogre::Viewport;
class Ogre::Camera;
class Ogre::RenderWindow;
class ExampleFrameListener;

class CHouseOfPhthah : public Ogre::Singleton< CHouseOfPhthah >
{
public :
	CHouseOfPhthah();
	~CHouseOfPhthah();

	static CHouseOfPhthah& getSingleton(void);
    static CHouseOfPhthah* getSingletonPtr(void);

	bool Start();
	void Run();
	void Exit();
	
public:
	Ogre::Root*				mRoot;
	Ogre::SceneManager*		mSceneMgr;
	Ogre::Viewport*			mViewport;
	Ogre::Camera*			mCamera;
    Ogre::RenderWindow*		mWindow;
	Ogre::String			mResourcePath;
	ExampleFrameListener*	mFrameListener;

private:
	bool		configure();
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
	CWater		mWater;
};

#endif //_HouseOfPhthah_