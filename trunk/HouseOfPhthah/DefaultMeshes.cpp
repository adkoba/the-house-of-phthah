#include <OgreEntity.h>
#include <OgreFrameListener.h>
#include <OgreMaterialManager.h> 
#include <OgreRoot.h>

#include "DefaultMeshes.h"
#include "HouseOfPhthah.h"

CDefaultMeshes::CDefaultMeshes()
	:	mSponzaEntityId("")
{
}

CDefaultMeshes::~CDefaultMeshes()
{
	deleteDefaultMeshes();
}

void CDefaultMeshes::createDefaultMeshes()
{
	SceneManager* sceneMgr = CHouseOfPhthah::getSingleton().getSceneMgr();
	Entity* entity = 0;
	String		materialName;
	String		meshName;
	SceneNode*	sceneNode;

	// We consider the ground to be a 10000x10000 square, beginning at (0,0), maxHeight == 100, see terrain.cfg
	{
		// name of the resources are given
		meshName = "Sponza.mesh";
		//mMaterialName = "Examples/CloudySky";
		mSponzaEntityId = mSponzaNodeId = "SponzaAtrium";

		// Create new entity
		entity = sceneMgr->createEntity(mSponzaEntityId, meshName);
		//mSkyDomeEntity->setMaterialName(mMaterialName);
		//mSkyDomeEntity->setRenderQueueGroup(Ogre::RENDER_QUEUE_SKIES_EARLY);
		//MaterialPtr m = MaterialManager::getSingleton().getByName(mMaterialName);
		// Make sure the material doesn't update the depth buffer
		//m->setDepthWriteEnabled(false);
		// Ensure loaded
		//m->load();

		// Create a SceneNode
		sceneNode = sceneMgr->getRootSceneNode()->createChildSceneNode(mSponzaNodeId, Vector3(5000,100,5000)/*center of the world*/ );
		// Bind the entity, to enable its rendering	
		sceneNode->attachObject(entity);
		// Scale the node (so all the attached entities to this node)
		sceneNode->scale(100,100,100);
	}
}

void CDefaultMeshes::deleteDefaultMeshes()
{
	SceneManager* sceneMgr = CHouseOfPhthah::getSingleton().getSceneMgr();
	sceneMgr->destroyEntity(mSponzaEntityId);
	mSponzaEntityId = "";
	sceneMgr->destroySceneNode(mSponzaNodeId);
	mSponzaNodeId = "";
}