#ifndef _Terrain_
#define _Terrain_

#include <Ogre.h>

using namespace Ogre;

// Event handler to add ability to alter curvature
class CTerrainListener: public FrameListener
{
public:
    CTerrainListener();
	virtual ~CTerrainListener();
    bool frameRenderingQueued(const FrameEvent& evt);
	void setRaySceneQuery(RaySceneQuery* const RaySceneQuery) { mRaySceneQuery = RaySceneQuery; };
private:
	Ray mUpdateRay;
	RaySceneQuery*	mRaySceneQuery;
};

class CTerrain
{
public:
	CTerrain();
	~CTerrain();
	// no exception is handled in case a terrain has already been pushed in a tree
	void createTerrain(const String TerrainId);
private:
	CTerrainListener* mListener;
	String mTerrainId;
};

#endif // _Terrain_