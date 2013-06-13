/*	GameObject.cpp
 *
 */
#include "GameObject.h"
#include "utils/ClException.h"

using std::string;
using namespace TSMG_NAME;

long TSMG CGameObject::m_idCounter= 0;

TSMG CGameObject::CGameObject()
	: CBaseObject(),
	  m_id(++m_idCounter),
	  m_className(string()),
	  m_position(TVertex()),
	  m_angles(TVertex())
	{}

TSMG CGameObject::CGameObject(
	const std::string& p_className)
	: CBaseObject(),
	  m_id(++m_idCounter),
	  m_className(p_className),
	  m_position(TVertex()),
	  m_angles(TVertex())
	{
	ExceptionSiVide(m_className);
	}

TSMG CGameObject::CGameObject(
	const std::string& p_className,
	const TVertex& p_position,
	const TVertex& p_angles)
	: CBaseObject(),
	  m_id(++m_idCounter),
	  m_className(p_className),
	  m_position(p_position),
	  m_angles(p_angles)
	{
	ExceptionSiVide(m_className);
	//TODO - Validate angles vextex's
	}

TSMG CGameObject::~CGameObject()
	{}

const long& TSMG CGameObject::Id() const
	{
	return m_id;
	}

const string& TSMG CGameObject::ClassName() const
	{
	return m_className;
	}

const TVertex& TSMG CGameObject::Position() const
	{
	return m_position;
	}

const TVertex& TSMG CGameObject::Angles() const
	{
	return m_angles;
	}