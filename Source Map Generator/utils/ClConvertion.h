/*	ClConvertion.h
 *		Les classes de ClConvertion.h font le pont entre les types numériques de base 
 *		et la classe standard de texte. Ainsi {ClConvertionTexte} et 
 *		{ClConvertionNumerique} effectuent les opérations nécessaire en une seule série 
 *		d'instruction ce que éclairci le code où elles sont utilisiée.
 *		Des typedef sont fournis pour faciliter leur fonctionnement.
 *
 *	Modifié le	:	2011-01-03
 */
#ifndef _CLCONVERTION_H_INLCUS_
#define _CLCONVERTION_H_INLCUS_

#include <sstream>
#include <string>

#include "utils.h"
#include "ClException.h"


_UTILGXT_DEBUT

// ClConvertionTexte
//	Fait la conversion entre {std::string} et un type numérique de base.
template <typename T>
class ClConvertionTexte
	{
	public:
		// ClConvertionTexte
		//	ClConvertionTexte de ClConvertionTexte.
		//	NB*	{p_texte} ne devrait contenir que l'expression à être 
		//		convertie. Si ce n'est pas le cas, ClConvertionTexte::Reusit()
		//		retournera {false}.
		ClConvertionTexte(
			const std::string& p_texte)		// Texte contenant la valeur
			: m_texte(p_texte)
			{
			ExceptionSiVide(m_texte);
			}

		// Resultat
		//	Retourne la valeur {T} du texte.
		//	NB*	{T} doit être {int}, {long}, {long long}, {double} ou {float}.
		T Resultat()
			{
			bool estMauvaisType= 
				typeid(T) != typeid(int)
				&& typeid(T) != typeid(double)
				&& typeid(T) != typeid(float)
				&& typeid(T) != typeid(long)
				&& typeid(T) != typeid(long long);
			ExceptionSi(T, estMauvaisType, 
				"Il est impossible d'effectuer une convertion sur le type donné.");

			return Convertisseur<T>(m_texte);
			}

		// Reussit
		//	Retourne l'état de la dernière opération éxécutée sur le texte.
		//	NB*	{true} si le texte ne contenait que l'expression. 
		//		{false} si non.
		bool Reussit() const
			{
			return m_reussit;
			}

	private:
		template <typename T>
		T Convertisseur(
			const std::string& p_texte)
			{
			istringstream iss(p_texte);
			T variableTemp;
			iss >> variableTemp;

			m_reussit= !iss.fail();
			if (m_reussit)
				{
				char c;
				iss >> c;
				m_reussit= iss.fail();
				}		

			return variableTemp;
			}

		std::string m_texte;
		bool m_reussit;
	};

// ClConvertionNumerique
//	Fait la convertion entre les types numériques de base et {std::string}.
template <typename T>
class ClConvertionNumerique
	{
	public:
		// ClConvertionNumerique
		//	Constructeur de ClConvertionNumerique.
		////
		// Lance une exception si le type donné n'est pas un des types numériques 
		//	de base : {int}, {long}, {long long}, {double} et {float}.
		ClConvertionNumerique(
			const T p_nombre)
			{
			bool estMauvaisType= 
				typeid(p_nombre) != typeid(int)
				&& typeid(p_nombre) != typeid(double)
				&& typeid(p_nombre) != typeid(float)
				&& typeid(p_nombre) != typeid(long)
				&& typeid(p_nombre) != typeid(long long);
			ExceptionSi(p_nombre, estMauvaisType, 
				"Il est impossible d'efftuer une convertion sur le type donné.");

			m_nombre= p_nombre;
			}

		// Texte
		//	Retourne le nombre sous forme de texte.
		const std::string& Resultat()
			{
			return Convertisseur(m_nombre);
			}

	private:
		std::string& Convertisseur(
			const T p_nombre)
			{
			std::ostringstream oss;
			oss << p_nombre;
			return (m_resultat= oss.str());
			}

		T m_nombre;
		std::string m_resultat;
	};

_UTILGXT_FIN


#define StringToInt(p_texte)		_UTILGXT ClConvertionTexte<int>((p_texte)).Resultat()
#define StringToLong(p_texte)		_UTILGXT ClConvertionTexte<long>((p_texte)).Resultat()
#define StringToLongLong(p_texte)	_UTILGXT ClConvertionTexte<long long>((p_texte)).Resultat()
#define StringToDouble(p_texte)		_UTILGXT ClConvertionTexte<double>((p_texte)).Resultat()
#define StringToFloat(p_texte)		_UTILGXT ClConvertionTexte<float>((p_texte)).Resultat()

#define IntToString(p_nombre)		_UTILGXT ClConvertionNumerique<int>((p_nombre)).Resultat()
#define LongToString(p_nombre)		_UTILGXT ClConvertionNumerique<long>((p_nombre)).Resultat()
#define LongLongToString(p_nombre)	_UTILGXT ClConvertionNumerique<long long>((p_nombre)).Resultat()
#define DoubleToString(p_nombre)	_UTILGXT ClConvertionNumerique<double>((p_nombre)).Resultat()
#define FloatToString(p_nombre)		_UTILGXT ClConvertionNumerique<float>((p_nombre)).Resultat()


#endif // _CLCONVERTION_H_INLCUS_