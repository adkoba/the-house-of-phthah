#ifndef __SKYDOME_H__
#define __SKYDOME_H__

#include <OgreSceneManager.h> // for Ogre::SceneManager::SkyDomeGenParameters

class CSkyDome
{
public:
	CSkyDome(	const Ogre::String& MaterialName = "",
				const Ogre::Real& Curv = 5,
				const Ogre::Real& Tiling = 8,
				const Ogre::Real& Distance = 4000 );
	CSkyDome(const CSkyDome& Copy);
	~CSkyDome();
	const Ogre::String& getPath() const { return mPath; };
	const Ogre::SceneManager::SkyDomeGenParameters& getParameters() const { return mParam; };
	void push(Ogre::SceneManager* SceneMgr, const bool& Enable = true, const bool& DrawFirst = true);
	void setCurvature(const Ogre::Real& Curv) { mParam.skyDomeCurvature = Curv; };
	void setDistance(const Ogre::Real& Distance) { mParam.skyDomeDistance = Distance; };
	void setPath(const Ogre::String& Path) { mPath = Path; };
	void setTiling(const Ogre::Real& Tiling) { mParam.skyDomeTiling = Tiling; };

private:
	Ogre::String		mPath;
	Ogre::SceneManager::SkyDomeGenParameters mParam;
};

#endif // __SKYDOME_H__