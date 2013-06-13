/*	ClObtenir.h
 *		Contient les déclarations nécessaires à l'utilisation de la classe de 
 *		saisie de donnée. 
 *
 *	Modifié le	:	2011-01-09
 */
#ifndef _CLOBTENIR_H_INCLUS_
#define _CLOBTENIR_H_INCLUS_

#include <cctype>	// toupper
#include <climits>
#include <iostream>
#include <locale>	// toupper
#include <sstream>
#include <string>

#include "utils.h"
#include "ClException.h"
#include "ClConvertion.h"

template <typename T>
class _ClObtenir
	{
	public:
		_ClObtenir()
			{};

		T Nombre(
			const std::string& p_question,
			const T& p_minimum,
			const T& p_maximum,
			const T& p_sentinelle)
			{
			ExceptionSiVide(p_question);

			T resultat;

			for(;;)
				{
				std::cout << p_question << " : ";
				std::string ligne;
				getline(std::cin, ligne);

				if (ligne.empty())
					{
					std::cout << "-> La saisie ne peut être vide.\n"; 
					continue;
					}

				_UTILGXT ClConvertionTexte<T> conv(ligne);
				resultat= conv.Resultat();
				if (!conv.Reussit())
					{
					std::cout << "-> La saisie ne peut : être vide, "
							  << "contenir des lettres, plusieurs nombres.\n"; 
					continue;
					}

				/***/
				if (p_minimum <= resultat && resultat <= p_maximum
					|| resultat == p_sentinelle) 
					break;
				/***/
				std::cout << "-> La saisie doit être comprise dans [" 
					<< p_minimum << " ; " << p_maximum
					<< "] ou être égale à <" << p_sentinelle << ">.\n";
				}

			return resultat;
			}

		std::string Texte(
			const std::string& p_question,
			const std::string::size_type p_longueurMin= 0,
			const std::string::size_type p_longueurMax= 80)
			{
			ExceptionSiVide(p_question);

			std::string ligne;

			for(;;)
				{
				std::cout << p_question << " : ";
				getline(std::cin, ligne);

				if (ligne.empty())
					{
					std::cout << "-> La saisie ne peut être vide.\n"; 
					continue;
					}

				/***/
				if (p_longueurMin <= ligne.size() && ligne.size() <= p_longueurMax)
					break;
				/***/
				std::cout << "-> La saisie doit avoir une longueur comprise dans [" 
					<< p_longueurMin << " ; " << p_longueurMax << "].\n";
				}

			return ligne;
			}
	};


_UTILGXT_DEBUT

// ObtnenirEntier
//	Par l'intermédiaire de la console une valeur entière est demandée à l'utilisateur, 
//	 qui est ensuite retournée.
int ObtnenirEntier(
	const std::string& p_question,			// Texte qui apparaîtra avant la saisie.
	const int& p_minimum= INT_MIN,			// Valeur minimale de l'entier.
	const int& p_maximum= INT_MAX,			// Valeur maximale de l'entier.
	const int& p_sentinelle= INT_MIN + 1)	// Valeur abitraire pouvant être à l'extérieur des limites précédentes.
	{
	return _ClObtenir<int>().Nombre(p_question, p_minimum, p_maximum, p_sentinelle);
	}

// ObtnenirDecimal
//	Par l'intermédiaire de la console une valeur décimale est demandée à l'utilisateur, 
//	 qui est ensuite retournée.
double ObtnenirDecimal(
	const std::string& p_question,			// Texte qui apparaîtra avant la saisie.
	const double& p_minimum= DBL_MIN,		// Valeur minimale de l'entier.
	const double& p_maximum= DBL_MAX,		// Valeur maximale de l'entier.
	const double& p_sentinelle= DBL_MIN + 1.0)	// Valeur abitraire pouvant être à l'extérieur des limites précédentes.
	{
	return _ClObtenir<double>().Nombre(p_question, p_minimum, p_maximum, p_sentinelle);
	}

// ObtnenirTexte
//	Par l'intermédiaire de la console du texte est demandé à l'utilisateur, 
//	 qui est ensuite retourné.
std::string ObtnenirTexte(
	const std::string& p_question,			// Texte qui apparaîtra avant la saisie.
	const std::string::size_type p_longueurMin,	// Longueur minimale (en caratères) du texte.
	const std::string::size_type p_longueurMax)	// Longueur maximale (en caratères) du texte.
	{
	return _ClObtenir<std::string>().Texte(p_question, p_longueurMin, p_longueurMax);
	}

// ObtnenirCaractere
//	Par l'intermédiaire de la console un caractère est demandé à l'utilisateur, 
//	 qui est ensuite retourné.
//	NB*	Dans le cas d'une lettre, le caractère sera en majuscule.
//	NB*	Les caractères accentués sont défectueux.
char ObtnenirCaractere(
	const std::string& p_question)			// Texte qui apparaîtra avant la saisie.
	{
	return std::toupper(*_ClObtenir<std::string>().Texte(p_question, 0, 1).begin());
	}

_UTILGXT_FIN

#endif // _CLOBTENIR_H_INCLUS_