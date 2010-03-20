#include "HOPEventDispatcher.h"
#include "CEventDispatcher.h"


namespace HOP
{

/*static*/ std::auto_ptr<IEventDispatcher> CHOPEventDispatcher::mEventDispatcher;

CHOPEventDispatcher::CHOPEventDispatcher()
{}

CHOPEventDispatcher::~CHOPEventDispatcher()
{}

/*static*/ IEventDispatcher* CHOPEventDispatcher::getEventDispatcher()
{
    if ( mEventDispatcher.get() == NULL )
	{
	    mEventDispatcher.reset( new CEventDispatcher() );
	}

    return mEventDispatcher.get();
}

}