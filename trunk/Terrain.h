#ifndef _Terrain_
#define _Terrain_

#include "ExampleFrameListener.h"

// Event handler to add ability to alter curvature
class CTerrainFrameListener : public ExampleFrameListener
{
public:
    CTerrainFrameListener(RenderWindow* win, Camera* cam, RaySceneQuery* raySceneQuery)
        : ExampleFrameListener(win, cam),
		  mRaySceneQuery(raySceneQuery)
    {
        // Reduce move speed
        mMoveSpeed = 50;
    }

    bool frameRenderingQueued(const FrameEvent& evt)
    {
        if( ExampleFrameListener::frameRenderingQueued(evt) == false )
		return false;

        // clamp to terrain
        static Ray updateRay;
        updateRay.setOrigin(mCamera->getPosition());
        updateRay.setDirection(Vector3::NEGATIVE_UNIT_Y);
        mRaySceneQuery->setRay(updateRay);
        RaySceneQueryResult& qryResult = mRaySceneQuery->execute();
        RaySceneQueryResult::iterator i = qryResult.begin();
        if (i != qryResult.end() && i->worldFragment)
        {
            mCamera->setPosition(mCamera->getPosition().x, 
                i->worldFragment->singleIntersection.y + 10, 
                mCamera->getPosition().z);
        }

        return true;

    }

	RaySceneQuery*		mRaySceneQuery;
};


class CTerrain
{
public:
	CTerrain();
	~CTerrain();

	void Init( std::string terrain_cfg );


private:
	void	createFrameListener();

	RaySceneQuery*			mRaySceneQuery;
	ExampleFrameListener*	mFrameListener;
};

#endif // _Terrain_