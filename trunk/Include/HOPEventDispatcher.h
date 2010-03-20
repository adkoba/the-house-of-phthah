#ifndef __HOP_EVENT_DISPATCHER_H__
#define __HOP_EVENT_DISPATCHER_H__

#ifdef	HOP_EVENT_DISPATCHER_BUILD
#define	EVENT_DISPATCHER_EXPORT	__declspec( dllexport )
#else
#define	EVENT_DISPATCHER_EXPORT	__declspec( dllimport )
#endif

#include <iostream>
#include <memory>
#include "IEventDispatcher.h"

namespace HOP
{
	/**
	 * \class   CHOPEventDispatcher
	 * \brief   Interface de chargement du module HOPEventDispatcher
	 * \author  FransTreb
	 * \date    22 nov. 2009
	 *
	 * Cette classe permet de charge l'interface IEventDispatcher. Elle impl�mente le
	 * design pattern Singleton, elle offre donc un acc�s unique au gestionnaire
	 * d'�venement. Aucune instance ne peut en �tre impl�ment�, tout se passe via 
	 * l'utilisation de sa m�thode statique.
	 */
	class EVENT_DISPATCHER_EXPORT CHOPEventDispatcher
	{
		private:
            /*!< Internal singleton */
            static std::auto_ptr<IEventDispatcher> mEventDispatcher;

			/**
			 * \brief Constructeur
			 */
			CHOPEventDispatcher();

        public:
			/**
			 * \brief Destructeur
			 */
			~CHOPEventDispatcher();

			/** 
			 * \brief Charge le gestionnaire d'event
			 *		\return Interface sur le gestionnaire
			 */
			static IEventDispatcher* getEventDispatcher();
	};
}

#endif // __HOP_EVENT_DISPATCHER_H__
