#ifndef _Default_Meshes_
#define _Default_Meshes_

#include <OgreString.h>

using namespace Ogre;

class CDefaultMeshes
{
public:
	
	// default constructor
	CDefaultMeshes();
private:
	// private copy constructor
	CDefaultMeshes(const CDefaultMeshes& Copy) { assert(false&&"CDefaultMeshes is non copyable."); };

public:
	// destructor
	~CDefaultMeshes();
	void createDefaultMeshes();
	void deleteDefaultMeshes();

private:

private:
	String		mSponzaEntityId;
	String		mSponzaNodeId;
};

#endif // _Default_Meshes_