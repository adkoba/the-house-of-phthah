#ifndef _SkyDome_
#define _SkyDome_

#include <Caelum.h>
#include <OgreFrameListener.h>
#include <OgreString.h>

using namespace Ogre;

class CSkyDomeListener: public Ogre::FrameListener
{
public:
	CSkyDomeListener(Camera* camera, SceneNode* skyDomeNode);
	virtual ~CSkyDomeListener();
	bool frameStarted(const Ogre::FrameEvent& evt);
private:
	Camera* mCamera;
	SceneNode* mSkyDomeNode;
    Caelum::CaelumSystem *mCaelumSystem;
};

class CSkyDome
{
public:
	CSkyDome();
private:
	CSkyDome(const CSkyDome& Copy);
public:
	~CSkyDome();
	// Bug: No exception handled if createSkyDome is called twice
	void createSkyDome(const Ogre::String MeshName, const Ogre::String MaterialName, const Ogre::String EntityId, const Ogre::String NodeId);
	const Ogre::String& getEntityId() const { return mEntityId; };
	const Ogre::String& getMaterialName() const { return mMaterialName; };
	const Ogre::String& getMeshName() const { return mMeshName; };
	const Ogre::String& getNodeId() const { return mNodeId; };

private:
	CSkyDomeListener*	mListener;
	Ogre::Entity*		mSkyDomeEntity;
	Ogre::String		mEntityId;
	Ogre::String		mMaterialName;
	Ogre::String		mMeshName;
	Ogre::String		mNodeId;
};

#endif // _SkyDome_