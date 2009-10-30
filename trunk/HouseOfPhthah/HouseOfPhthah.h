#ifndef _HouseOfPhthah_
#define _HouseOfPhthah_

#include <OgreSingleton.h>
#include <OgreString.h>
#include "IHouseOfPhthah.h"
#include "Macros.h"
#include "Sky.h"
#include "Terrain.h"
#include "Water.h"

class Ogre::Root;
class Ogre::SceneManager;
class Ogre::Viewport;
class Ogre::Camera;
class Ogre::RenderWindow;
class ExampleFrameListener;
class IEntityMgr;

class CHouseOfPhthah : public Ogre::Singleton< CHouseOfPhthah >
					 , public IHouseOfPhthah
{
public :
	CHouseOfPhthah();
	~CHouseOfPhthah();
	CSky& getSky() { return mSkyDome; };

	static CHouseOfPhthah& getSingleton(void);
    static CHouseOfPhthah* getSingletonPtr(void);

	Ogre::Camera*		getCamera() { return mCamera; }
	Ogre::SceneManager*	getSceneMgr() { return mSceneMgr; }
	Ogre::Root*			getRoot() { return mRoot; }

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
	IEntityMgr*				mEntityMgr;

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
	CSky		mSkyDome;
	CTerrain	mTerrain;
	CWater		mWater;
};

#endif //_HouseOfPhthah_