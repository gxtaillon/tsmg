/*	utils.h	
 *		Fichier principal, parent à tous les fichiers de l'utilitaires.
 *		Comprend les définitions relatives à ces derniers.
 *
 *		Les barres de soulignements utilisées à travers l'utilitaires 
 *		respectent cette simple pensée :
 *			«The underscore gained a cognitive association with system 
 *			 level programming, hidden technicalities, and the messy entrails
 *			 of language support.» - Wikipedia.org
 *
 *	Modifié le	:	2011-01-04
 */
#ifndef _UTILS_H_INCLUS_
#define _UTILS_H_INCLUS_

#define _UTILGXT_VERSION	"3.0"

#define _UTILGXT_NOM		__UtilitairesGXT
#define _UTILGXT_DEBUT		namespace _UTILGXT_NOM {
#define _UTILGXT_FIN		}
#define _UTILGXT			_UTILGXT_NOM::

// Utilitaires C++
_UTILGXT_DEBUT
_UTILGXT_FIN

namespace Utils= _UTILGXT_NOM;


// Autres

#ifndef NULL
#define NULL 0
#endif // NULL

#ifdef _MSC_VER
	#define _UTILGXT_WINDOWS

	#ifndef __func__
	#define __func__ __FUNCTION__ // __FUNCSIG__

	#endif	// __func__

#else	// _MSC_VER	
#ifdef __GNUC__
	#define _UTILGXT_LINUX
	#ifndef __func__
	#define __func__ __PRETTY_FUNCTION__

	#endif	// __func__

#endif	// __GNUC__
#endif	// _MSC_VER

#endif // _UTILS_H_INCLUS_