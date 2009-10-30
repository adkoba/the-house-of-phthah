#include "CEntityManager.h"
#include "IHouseOfPhthah.h"
#include "Character.h"
#include "LocalPlayer.h"
#include "Ennemy.h"

#include <iostream>
#include <sstream>

#include <OgreRoot.h>
#include <OgreNode.h>
#include <OgreEntity.h>

#include "Macros.h"

CEntityMgr::CEntityMgr()
	: mNbEntityLoaded(0)
	, mRaySceneQuery(NULL)
{}

CEntityMgr::~CEntityMgr()
{}

void CEntityMgr::loadEntity( const std::string& pFileName )
{}

void CEntityMgr::addEntity( HOPEntityType pEntityType, const std::string& pEntityName, Ogre::Vector3& pPosition )
{
	// Create the player name
	std::ostringstream lOss;
	lOss << "Entity_" << mNbEntityLoaded;
	std::string lEntityName = lOss.str();

	// Create a new instance of a player
	Ogre::SceneManager* lSceneMgr = mHOP->getSceneMgr();
	Ogre::Entity *ent = lSceneMgr->createEntity(lEntityName, pEntityName);

	lOss << "_Node";

	// Set the y value depends on height of the map on this point
	Ogre::Ray lNewPlayerRay(Ogre::Vector3(pPosition.x, 5000.0f, pPosition.z), Ogre::Vector3::NEGATIVE_UNIT_Y);
	mRaySceneQuery = lSceneMgr->createRayQuery(lNewPlayerRay);

	Ogre::RaySceneQueryResult & lResult = mRaySceneQuery->execute();
	
	Ogre::RaySceneQueryResult::iterator lIt = lResult.begin();
	if( lIt != lResult.end() && lIt->worldFragment )
	{
		pPosition.y = lIt->worldFragment->singleIntersection.y;
	}

	Ogre::SceneNode *lNode = lSceneMgr->getRootSceneNode()->createChildSceneNode(lOss.str(),pPosition);
	lNode->attachObject(ent);
	lNode->setScale(0.1f, 0.1f, 0.1f);

	// Add this instance in the SceneMgr
	CCharacter* lNewCharacter;
	switch(pEntityType)
	{
		case Player: lNewCharacter = new CLocalPlayer(lNode, ent, lEntityName);
			break;
		case Ennemy: lNewCharacter = new CEnnemy(lNode, ent, lEntityName);
			break;
	}
	//CHouseOfPhthah::getSingletonPtr()->mRoot->addFrameListener(lNewCharacter);
	mCharacterList.push_back(lNewCharacter);

	// We increment the number of entity load in the scene
	mNbEntityLoaded++;
}