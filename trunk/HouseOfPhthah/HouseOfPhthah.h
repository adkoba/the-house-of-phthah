#ifndef _HouseOfPhthah_
#define _HouseOfPhthah_

#include <OgreSingleton.h>
#include <OgreString.h>
#include "IHouseOfPhthah.h"
#include "Macros.h"
#include "Sky.h"
#include "Terrain.h"
#include "Water.h"
#include "DefaultMeshes.h"

namespace Ogre
{
	class Ogre::Root;
	class Ogre::SceneManager;
	class Ogre::Viewport;
	class Ogre::Camera;
	class Ogre::RenderWindow;
}

namespace HOP
{
	class CHOPFrameListener;
	class CCamera;
}
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

	HOP::CCamera*		getCamera() { return mCamera; }
	Ogre::SceneManager*	getSceneMgr() { return mSceneMgr; }
	Ogre::Root*			getRoot() { return mRoot; }

	bool Start();
	void Run();
	void Exit();
	
public:
	Ogre::Root*				mRoot;
	Ogre::SceneManager*		mSceneMgr;
	Ogre::Viewport*			mViewport;
    Ogre::RenderWindow*		mWindow;
	Ogre::String			mResourcePath;
	HOP::CHOPFrameListener*	mFrameListener;
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
	HOP::CCamera*	mCamera;
	CSky			mSkyDome;
	CTerrain		mTerrain;
	CWater			mWater;
	CDefaultMeshes	mWorldMeshes;
};

#endif //_HouseOfPhthah_