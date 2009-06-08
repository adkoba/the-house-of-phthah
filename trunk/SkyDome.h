#ifndef _SkyDome_
#define _SkyDome_

#include <Ogre.h>

class CSkyDome
{
public:
	CSkyDome();
	CSkyDome(const CSkyDome& Copy);
	~CSkyDome();
	const Ogre::String& getMaterialName() const { return mMaterialName; };
	const Ogre::String& getMeshName() const { return mMeshName; };
	//void push(bool enable = true) { Ogre::Singleton<CHouseOfPhthah>::getSingleton().mSceneMgr->setSkyDome(enable, mPath); };
	void setMaterialName(const Ogre::String& materialName) { mMaterialName = materialName; };
	void setMeshName(const Ogre::String& meshName) { mMeshName = meshName; };
	void createSkyDome();

private:
	Ogre::String mMaterialName;
	Ogre::String mMeshName;
	Ogre::SceneNode* mSkyDomeNode;
	Ogre::Entity* mSkyDomeEntity;
	const Ogre::String mNodeId;
	const Ogre::String mEntityId;
};

#endif // _SkyDome_