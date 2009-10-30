#ifndef _HOP_C_ENTITY_MGR_
#define _HOP_C_ENTITY_MGR_

#include "IEntityManager.h"
#include "IHouseOfPhthah.h"
#include "CFrameListener.h"
#include "Character.h"

typedef std::vector<CCharacter*>	CCharacterList;

class CEntityMgr : public IEntityMgr
{
private:
	int						mNbEntityLoaded;
	Ogre::RaySceneQuery*	mRaySceneQuery;
	CCharacterList			mCharacterList;
	IHouseOfPhthah*			mHOP;

public:
	/**
	 * \brief Constructor
	 */
	CEntityMgr();

	/**
	 * \brief Destructor
	 */
	virtual ~CEntityMgr();

	////////////////////////////////////////////
	// Implementation needed by CFrameListener
	////////////////////////////////////////////

	/**
	 * \brief Called when a frame is about to begin rendering.
	 *		\param[in]	pEvt	Event data
	 *		\return Return if stop is needed
	 */
	bool frameStarted(const Ogre::FrameEvent& evt) { return true; }

	///////////////////////////////////////
	// Implementation needed by IEntityMgr
	///////////////////////////////////////

	void setHOP( IHouseOfPhthah* pIntr ) { mHOP = pIntr; }
	/**
	 * \brief Loads level entities from a description file
	 *		\param[in]	pFile	Level description file
	 */
	void loadEntity( const std::string& pFile );

	/**
	 * \brief Add a player in the scene
	 *		\param[in]	pEntityType	Player's type to add in the scene
	 *		\param[in]	pEntityName	Name entity to used to load 3d model
	 *		\param[in]	pPositon	Entity's postion in the map
	 *		\throw	EntityException
	 */
	void addEntity( HOPEntityType pEntityType, const std::string& pEntityName, Ogre::Vector3& pPosition ) /*throw CEntityException*/;
};

#endif // _HOP_C_ENTITY_MGR_