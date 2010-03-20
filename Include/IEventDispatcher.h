#ifndef __I_EVENT_DISPATCHER__
#define __I_EVENT_DISPATCHER__

#include "IInputEventDispatcher.h"

// Forward declaration
namespace Ogre
{
	class RenderWindow;
	class FrameListener;
}

namespace HOP
{
	/**
	 * \class   IEventDispatcher
	 * \brief   Interface de gestion de l'enregistrement de FrameEvent listener
	 * \author  FransTreb
	 * \date    22 nov. 2009
	 */
	class IEventDispatcher : public IInputEventDispatcher
	{
		public:
			virtual ~IEventDispatcher() {}

			/**
			 * \brief Initialise le module de gestion des evenements
			 *		\param[in] pWindow	Window utilisee par l'application
			 */
			virtual void	initialize(Ogre::RenderWindow* pWindow) = 0;

			/**
			 * \brief Libère les ressources utilisées par le gestionnaire
			 *		\param[in] pWindow	Window utilisee par l'application
			 */
			virtual void	close(Ogre::RenderWindow* pWindow) = 0;

			/**
			 *	\brief Get the FrameListener interface
			 *		\return FrameListerner ptr
			 */
			virtual Ogre::FrameListener*	getFrameListener() = 0;

	}; /* End of IEventDispatcher */

} /* End of namespace */

#endif /* __I_EVENT_DISPATCHER__ */