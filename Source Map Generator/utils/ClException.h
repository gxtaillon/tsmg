/*	ClException.h
 *		Contient les déclarations nécessaires à l'utilistion de la classe
 *		d'exception ainsi que quelques macros commandes facilitant leur 
 *		utilisation.
 *
 *	Modifié le	:	2011-02-05
 *	Note:
 *		Messages traduit en anglais.
 */
#ifndef _CLEXCEPTION_H_INCLUS_
#define _CLEXCEPTION_H_INCLUS_

#include <exception>
#include <string>

#include "utils.h"


#ifdef _MSC_VER	// Visual C++
// C4290 : Support absent pour la spécification des exceptions
#pragma warning( disable : 4290 )
#endif // _MSC_VER


_UTILGXT_DEBUT

// ClException
//	Objet pouvant être lancé pour donner les détails d'un cas anormal 
//	 lors de l'éxécution.
//	L'exception peut être inscrite dans un fichier journal dont le 
//	 chemin est donné par {ClException::JOURNAL_CHEMIN}.
class ClException : public std::exception
	{
	public:
		// ClException
		//	Constructeur de ClException. 
		//	NB* Il est préférable d'utiliser les macros commandes 
		//		Exception(p_desc) et ExceptionEnregistree(p_desc) qui 
		//		s'occupent de fournir automatiquement tous les paramètres
		//		sauf la description.
		ClException(
			const std::string& p_fichier,		// Fichier contenant l'erreur
			const int p_ligne,					// Ligne du fichier 
			const std::string& p_fonction,		// Fonction ayant lancée l'exception
			const std::string& p_description,	// Description du problème
			const bool p_estEnregistree= false)	// Si VRAI, l'exception sera inscrite dans le fichier journal
			throw(_UTILGXT ClException);

		// Fichier
		//	Retourne le nom du fichier d'où provient l'exception.
		const std::string& Fichier() const throw();

		// Ligne
		//	Retourne le numéro de la ligne du fichier.
		int Ligne() const throw();

		// Fonction
		//	Retourne le nom de la fonction ayant construite l'exception.
		const std::string& Fonction() const throw();

		// Description
		//	Retourne la description donnée au problème rencontré.
		const std::string& Description() const throw();

		// what [Héritée]
		//	Retourne l'ensemble des données disponibles sur le problème 
		//	 sous la forme : "<Fonction> : <Description>".
		virtual const char* what() const throw();

		// Définie le dossier où sera enregistré le journal.
		//	NB*	Est par défaut sur {<Dossier d'éxécution>/exceptions.log}
		static std::string JOURNAL_CHEMIN;

	protected:
		bool Enregistrer() const throw();

		std::string m_fichier;
		int m_ligne;
		std::string m_fonction;
		std::string m_description;
		std::string m_what;
		
	};

_UTILGXT_FIN


#define Exception(p_desc)					_UTILGXT ClException(__FILE__, __LINE__, __func__, (p_desc));
#define ExceptionEnregistree(p_desc)		_UTILGXT ClException(__FILE__, __LINE__, __func__, (p_desc), true);

#define ExceptionSi(p_var, p_cond, p_desc)	if ((p_cond)) throw ExceptionEnregistree(p_desc ## " ( " #p_var " )");
#define ExceptionSiVide(p_var)				ExceptionSi(p_var, (p_var).empty(),	"The variable cannot be empty.");
#define ExceptionSiZero(p_var)				ExceptionSi(p_var, (p_var) == 0, "The variable cannot be equal to zero.");


#endif // _CLEXCEPTION_H_INCLUS_