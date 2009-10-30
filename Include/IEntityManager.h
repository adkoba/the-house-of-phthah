#ifndef _HOP_I_ENTITY_MGR_
#define _HOP_I_ENTITY_MGR_

#include "HOPTypes.h"
#include "OgreVector3.h"
#include <string>

class IHouseOfPhthah;

class IEntityMgr
{
public:

	virtual void setHOP( IHouseOfPhthah* pIntr ) = 0;

	/**
	 * \brief Loads level entities from a description file
	 *		\param[in]	pFile	Level description file
	 */
	virtual void loadEntity( const std::string& pFile ) = 0;

	/**
	 * \brief Add a player in the scene
	 *		\param[in]	pEntityType	Player's type to add in the scene
	 *		\param[in]	pEntityName	Name entity to used to load 3d model
	 *		\param[in]	pPositon	Entity's postion in the map
	 *		\throw	EntityException
	 */
	virtual void addEntity( HOPEntityType pEntityType, const std::string& pEntityName, Ogre::Vector3& pPosition ) /*throw CEntityException*/ = 0;
};

#endif // _HOP_I_ENTITY_MGR_