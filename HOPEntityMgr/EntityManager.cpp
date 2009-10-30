#include "EntityManager.h"
#include "CEntityManager.h"

IEntityMgr* managerInstance = NULL;

IEntityMgr* loadEntityMgr()
{
	if( managerInstance == NULL )
	{
		managerInstance = new CEntityMgr();
	}

	return managerInstance;
}

void unloadEntityMgr()
{
	delete managerInstance;
	managerInstance = NULL;
}