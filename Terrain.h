#ifndef _Terrain_
#define _Terrain_

#include "ExampleFrameListener.h"

class CTerrain
{
public:
	CTerrain();
	~CTerrain();
	void Init( const std::string& terrain_cfg );

private:
	RaySceneQuery*			mRaySceneQuery;
};

#endif // _Terrain_