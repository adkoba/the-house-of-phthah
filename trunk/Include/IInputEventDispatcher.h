#ifndef _HOP_I_INPUT_LISTENER_
#define _HOP_I_INPUT_LISTENER_

#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

namespace HOP
{
	/**
	 * \class   IInputEventDispatcher
	 * \brief   Interface de gestion de l'enregistrement d'Input listener
	 * \author  FransTreb
	 * \date    22 nov. 2009
	 *
	 */
	class IInputEventDispatcher
	{
		protected:

		public:
			virtual ~IInputEventDispatcher() {}

			/** 
			 * \brief Register a listener of Mouse Event
			 *		\param[in] pListenerName Name of the listener used to identify the listener
			 *		\param[in] pIntr		 Interface to call
			 */
			virtual void registerMouseListerner( const std::string& pListenerName, OIS::MouseListener* pIntr ) = 0;
			/** 
			 * \brief Unregister a listener of Mouse Event
			 *		\param[in] pListenerName Name of the listener used to identify the listener
			 */
			virtual void unregisterMouseListerner( const std::string& pListenerName ) = 0;

			/** 
			 * \brief Register a listener of Keyboard Event
			 *		\param[in] pListenerName Name of the listener used to identify the listener
			 *		\param[in] pIntr		 Interface to call
			 */
			virtual void registerKeyboardListerner( const std::string& pListenerName, OIS::KeyListener* pIntr ) = 0;
			/** 
			 * \brief Unregister a listener of Keyboard Event
			 *		\param[in] pListenerName Name of the listener used to identify the listener
			 */
			virtual void unregisterKeyboardListerner( const std::string& pListenerName ) = 0;

	};/* End of IInputEventDispatcher */

} /* End of namespace */

#endif // _HOP_I_INPUT_LISTENER_