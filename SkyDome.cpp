#include "SkyDome.h"

#include "HouseOfPhthah.h"

CSkyDome::CSkyDome(const Ogre::String& MaterialName):
	mSkyDomeEntity(NULL),
	mPath(MaterialName)
{
}

	CSkyDome::CSkyDome(const CSkyDome& Copy):
	mPath(Copy.mPath)
{
}

CSkyDome::~CSkyDome()
{
}

void CSkyDome::push(bool enable)
{
	Ogre::Singleton<CHouseOfPhthah>::getSingleton().mSceneMgr->setSkyDome(enable, mPath);
}

void CSkyDome::setSkyDome(const Ogre::String &materialName)
{
	//MaterialPtr m = Ogre::MaterialManager::getSingleton().getByName(materialName);
//      if (m.isNull())
//      {
//          OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, 
//              "Sky dome material '" + materialName + "' not found.",
//              "SceneManager::setSkyDome");
//      }
    //// Make sure the material doesn't update the depth buffer
    //m->setDepthWriteEnabled(false);
    //// Ensure loaded
    //m->load();

	Ogre::SceneNode* SkyDomeNode = Ogre::Singleton<CHouseOfPhthah>::getSingleton().mSceneMgr->getSkyDomeNode();
	Ogre::SceneManager* SceneMgr = Ogre::Singleton<CHouseOfPhthah>::getSingleton().mSceneMgr;

    //mSkyDomeDrawFirst = drawFirst;
	//mSkyDomeRenderQueue = renderQueue;

    // Create node 
    if (!SkyDomeNode)
    {
        SkyDomeNode = SceneMgr->createSceneNode("SkyDomeNode");
		SkyDomeNode->scale(10,10,10);
    }
    else
    {
        SkyDomeNode->detachAllObjects();
    }

	Ogre::String entName = "PhthahSkyDome";

    // Create entity 
    if (mSkyDomeEntity)
    {
        // destroy old one, do it by name for speed
        SceneMgr->destroyEntity(entName);
    }
	
	mSkyDomeEntity = SceneMgr->createEntity(entName, "PhthahSkyDome.mesh");

	SkyDomeNode->attachObject(mSkyDomeEntity);
	

//     // Set up the dome (5 planes)
//     for (int i = 0; i < 5; ++i)
//     {
//         MeshPtr planeMesh = createSkydomePlane((BoxPlane)i, curvature, 
//             tiling, distance, orientation, xsegments, ysegments, 
//             i!=BP_UP ? ySegmentsToKeep : -1, groupName);

//         String entName = "SkyDomePlane" + StringConverter::toString(i);

        //// Create entity 
        //if (mSkyDomeEntity[i])
        //{
        //    // destroy old one, do it by name for speed
        //    destroyEntity(entName);
        //}
		//// construct manually so we don't have problems if destroyAllMovableObjects called
		//MovableObjectFactory* factory = 
		//	Root::getSingleton().getMovableObjectFactory(EntityFactory::FACTORY_TYPE_NAME);
		//NameValuePairList params;
		//params["mesh"] = planeMesh->getName();
		//mSkyDomeEntity[i] = static_cast<Entity*>(factory->createInstance(entName, this, &params));
//         mSkyDomeEntity[i]->setMaterialName(m->getName());
//         mSkyDomeEntity[i]->setCastShadows(false);

//     } // for each plane
}