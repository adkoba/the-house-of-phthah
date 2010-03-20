#include "HOPFrameListener.h"
#include "HOPCamera.h"
#include "HouseOfPhthah.h"
#include "Globals.h"
#include "HOPEventDispatcher.h"

#include <Ogre.h>

namespace HOP
{

// Constructor takes a RenderWindow because it uses that to determine input context
CHOPFrameListener::CHOPFrameListener(RenderWindow* win) 
:	mWindow(win),
	mStatsOn(true),
	mNumScreenShots(0),
	mFiltering(TFO_BILINEAR),
	mAniso(1),
	mSceneDetailIndex(0),
	mDebugOverlay(0),
	mQuit(false)
{
	mDebugOverlay = OverlayManager::getSingleton().getByName("Core/DebugOverlay");

	showDebugOverlay(true);

	// Register as Keyboard Listener
    HOP::CHOPEventDispatcher::getEventDispatcher()->registerKeyboardListerner("HOPFrameListener",this);

}

CHOPFrameListener::~CHOPFrameListener()
{
}

// Override frameRenderingQueued event to process that (don't care about frameEnded)
bool CHOPFrameListener::frameRenderingQueued(const FrameEvent& evt)
{
	if(mWindow->isClosed())	return false;

	return true;
}

//bool CHOPFrameListener::processUnbufferedKeyInput(const FrameEvent& evt)
bool CHOPFrameListener::keyPressed( const OIS::KeyEvent &arg )
{
	if( arg.key == OIS::KC_ESCAPE || arg.key == OIS::KC_Q )
		mQuit = true;

	if( arg.key == OIS::KC_F )
	{
		mStatsOn = !mStatsOn;
		showDebugOverlay(mStatsOn);
	}

	if( arg.key == OIS::KC_T )
	{
		switch(mFiltering)
		{
			case TFO_BILINEAR:
				mFiltering = TFO_TRILINEAR;
				mAniso = 1;
				break;
			case TFO_TRILINEAR:
				mFiltering = TFO_ANISOTROPIC;
				mAniso = 8;
				break;
			case TFO_ANISOTROPIC:
				mFiltering = TFO_BILINEAR;
				mAniso = 1;
				break;
			default: break;
		}
		MaterialManager::getSingleton().setDefaultTextureFiltering(mFiltering);
		MaterialManager::getSingleton().setDefaultAnisotropy(mAniso);

		showDebugOverlay(mStatsOn);
	}

	if( arg.key == OIS::KC_SYSRQ )
	{
		std::ostringstream ss;
		ss << "screenshot_" << ++mNumScreenShots << ".png";
		mWindow->writeContentsToFile(ss.str());
		mDebugText = "Saved: " + ss.str();
	}

	// Control the height of the water:
	if( arg.key == OIS::KC_ADD )
	{
		CGlobals::waterHeight += 1.0f;
	}
	if( arg.key == OIS::KC_MINUS )
	{
		CGlobals::waterHeight -= 1.0f;
	}
	// Change the type of sky
	if( arg.key == OIS::KC_Z )
	{
		CHouseOfPhthah::getSingleton().getSky().switchSkyType();
	}

	// Return true to continue rendering
	return true;
}

void CHOPFrameListener::updateStats()
{
	static String currFps = "Current FPS: ";
	static String avgFps = "Average FPS: ";
	static String bestFps = "Best FPS: ";
	static String worstFps = "Worst FPS: ";
	static String tris = "Triangle Count: ";
	static String batches = "Batch Count: ";

	// update stats when necessary
	try {
		OverlayElement* guiAvg = OverlayManager::getSingleton().getOverlayElement("Core/AverageFps");
		OverlayElement* guiCurr = OverlayManager::getSingleton().getOverlayElement("Core/CurrFps");
		OverlayElement* guiBest = OverlayManager::getSingleton().getOverlayElement("Core/BestFps");
		OverlayElement* guiWorst = OverlayManager::getSingleton().getOverlayElement("Core/WorstFps");

		const RenderTarget::FrameStats& stats = mWindow->getStatistics();
		guiAvg->setCaption(avgFps + StringConverter::toString(stats.avgFPS));
		guiCurr->setCaption(currFps + StringConverter::toString(stats.lastFPS));
		guiBest->setCaption(bestFps + StringConverter::toString(stats.bestFPS)
			+" "+StringConverter::toString(stats.bestFrameTime)+" ms");
		guiWorst->setCaption(worstFps + StringConverter::toString(stats.worstFPS)
			+" "+StringConverter::toString(stats.worstFrameTime)+" ms");

		OverlayElement* guiTris = OverlayManager::getSingleton().getOverlayElement("Core/NumTris");
		guiTris->setCaption(tris + StringConverter::toString(stats.triangleCount));

		OverlayElement* guiBatches = OverlayManager::getSingleton().getOverlayElement("Core/NumBatches");
		guiBatches->setCaption(batches + StringConverter::toString(stats.batchCount));

		if( mDebugText != "" )
		{
			OverlayElement* guiDbg = OverlayManager::getSingleton().getOverlayElement("Core/DebugText");
			guiDbg->setCaption(mDebugText);
		}
	}
	catch(...) { /* ignore */ }
}

} // End of namespace