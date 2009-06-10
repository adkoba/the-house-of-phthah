#ifndef _SkyDome_
#define _SkyDome_

#include <Ogre.h>

class CSkyDomeListener: public Ogre::FrameListener
{
public:
	CSkyDomeListener();
	virtual ~CSkyDomeListener();
	bool frameStarted(const Ogre::FrameEvent& evt);
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);
	void setNodeId(const Ogre::String& NodeId) { mNodeId = &NodeId; };
private:
	const Ogre::String* mNodeId;
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