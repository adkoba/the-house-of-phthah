#ifndef __ENTITY_MGR_H__
#define __ENTITY_MGR_H__

#include "IEntityManager.h"

#ifndef	HOPENTITYMGR_EXPORTS
#define	EntityMgrExport	__declspec( dllimport )
#else
#define	EntityMgrExport	__declspec( dllexport )
#endif

extern "C" EntityMgrExport	IEntityMgr* loadEntityMgr( );
extern "C" EntityMgrExport	void unloadEntityMgr();

#endif
