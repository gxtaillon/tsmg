/*	GameObject.h
 *		{CGameObject} is the lowest level of /object/ that exists in a 
 *		map.
 *
 */
#pragma once
#include <string>
#include "BaseObject.h"
#include "Types.h"

TSMG_BEGIN

inline std::string FormatForPrinting(
	const std::string& p_attribute,
	const std::string& p_value)
	{
	return std::string("\"" + p_attribute + "\" \"" + p_value + "\"\n");
	}

class CGameObject :
	public CBaseObject
	{
	public:
		CGameObject();
		CGameObject(
			const std::string& p_className);
		CGameObject(
			const std::string& p_className,
			const TVertex& p_position,
			const TVertex& p_angles);
		~CGameObject();

		const long& Id() const;
		const std::string& ClassName() const;
		const TVertex& Position() const;
		const TVertex& Angles() const;
		virtual void Print(
			std::ofstream& p_file) const = 0;

	protected:
		long m_id;
		std::string m_className;
		TVertex m_position;
		TVertex m_angles;

	private:
		static long m_idCounter;
	};

TSMG_END