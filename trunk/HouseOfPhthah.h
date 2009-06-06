#ifndef _HouseOfPhthah_
#define _HouseOfPhthah_

#include <Ogre.h>

class CHouseOfPhthah
{
public :
	CHouseOfPhthah();
	~CHouseOfPhthah();
	
	void Start();
	void Run();
	void Exit();
	
public :
	Ogre::Root*			m_Root;
	Ogre::SceneManager* m_SceneMgr;
	Ogre::Viewport*		m_Viewport;
	Ogre::Camera*		m_Camera;
    Ogre::RenderWindow*		m_Window;
	Ogre::String			m_ResourcePath;

private:
	void		configure();
	void		chooseSceneManager();
	void		createCamera();
	void		createScene();
	void		destroyScene();
	void		createViewports();
	void		setupResources();
	void		loadResources();
};

#endif //_HouseOfPhthah_