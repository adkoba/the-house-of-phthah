#ifndef _Sky_
#define _Sky_

#include <Caelum.h>
#include <OgreString.h>

using namespace Ogre;

class CSkyListener;

class CSky
{
public:
	enum eSkyType
	{
		OGRE_SKY_PLANE,
		OGRE_SKY_BOX,
		OGRE_SKY_DOME,
		PHTHAH_SKY_DOME,
		CAELUM_SKY_DOME
	};
	// default constructor
	CSky();
private:
	// private copy constructor
	CSky(const CSky& Copy) { assert(false&&"CSky is non copyable."); };
public:
	// destructor
	~CSky();
	void createSky(const eSkyType& SkyType);
	void deleteSky();
	Caelum::CaelumSystem* getCaelumSystem() const { return mCaelumSystem; };
	const Ogre::String& getEntityId() const { return mEntityId; };
	const Ogre::String& getMaterialName() const { return mMaterialName; };
	const Ogre::String& getMeshName() const { return mMeshName; };
	const Ogre::String& getNodeId() const { return mNodeId; };
	const eSkyType& getSkyType() const { return mSkyType; };
	void switchSkyType();

private:
	// method to create the sky
	void createCaelumSkyDome();
	void createOgreSkyPlane();
	void createOgreSkyBox();
	void createOgreSkyDome();
	void createPhthahSkyDome();
	// method to delete the sky
	void deleteCaelumSkyDome();
	void deleteOgreSkyPlane();
	void deleteOgreSkyBox();
	void deleteOgreSkyDome();
	void deletePhthahSkyDome();

private:
	// listenerto set the sky above the camera
	CSkyListener*	mListener;
	// sky type
	eSkyType mSkyType;
	// caelum sky attributes
	Caelum::CaelumSystem* mCaelumSystem;
	// phthah sky attributes
	Ogre::Entity*		mSkyDomeEntity;
	Ogre::String		mEntityId;
	Ogre::String		mMaterialName;
	Ogre::String		mMeshName;
	Ogre::String		mNodeId;
};

#endif // _Sky_