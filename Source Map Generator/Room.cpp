/*	Room.cpp
 *
 */
#include <fstream>
#include "Room.h"
#include "utils/ClException.h"

using namespace TSMG_NAME;

TSMG CRoom::CRoom()	
	: CGameObject(
		TSMG_BRUSH_CLASSNAME,
		TVertex(), TVertex()),
	  m_size(TVertex()),
	  m_material(TSMG_ROOM_MATERIAL),
	  m_settings(0)
	{}

TSMG CRoom::CRoom(
	const TVertex& p_position,	
	const TVertex& p_angles,
	const TVertex& p_size,
	const std::string& p_genericMaterial,
	const unsigned short p_settings)	
	: CGameObject(
		TSMG_BRUSH_CLASSNAME,
		p_position, p_angles),
	  m_size(p_size),
	  m_material(p_genericMaterial),
	  m_settings(p_settings)
	{
	ExceptionSiVide(m_material);
	ExceptionSi(m_settings, 0 > m_settings || m_settings > WALL_ALL, "Bad settings. Use predefined values of CRoom for optimum functionnality.");

	GenerateWalls();
	}

TSMG CRoom::~CRoom()
	{
	for (int i= m_walls.size() - 1; i >= 0; --i)
		{
		delete m_walls[i];
		m_walls.pop_back();
		}
	}

void TSMG CRoom::Print(
	std::ofstream& p_oFile) const
	{
	ExceptionSi(p_oFile, !p_oFile.is_open(), "The file could not be opened for writing.");

	for (int i= 0; i != m_walls.size(); ++i)
		m_walls[i]->Print(p_oFile);
	}

void TSMG CRoom::Settings(
	const unsigned short p_settings)
	{
	ExceptionSi(p_settings, 0 > p_settings || p_settings > WALL_ALL, "Bad settings. Use predefined values of CRoom for optimum functionnality.");
	m_settings= p_settings;
	}

unsigned short TSMG CRoom::Settings() const
	{
	return m_settings;
	}

void TSMG CRoom::GenerateWalls()
	{
	if ((m_settings & WALL_RIGHT) == WALL_RIGHT)
		{
		m_walls.push_back(new CBrush(
			TVertex(
				m_position.x + m_size.x/2 + CBrush::DEFAULT_SIZE.x/2, 
				m_position.y,
				m_position.z),
			TVertex(0,0,0),
			TVertex(
				CBrush::DEFAULT_SIZE.x, 
				m_size.y,
				m_size.z),
			m_material));
		}

	if ((m_settings & WALL_LEFT) == WALL_LEFT)
		{
		m_walls.push_back(new CBrush(
			TVertex(
				m_position.x - m_size.x/2 - CBrush::DEFAULT_SIZE.x/2, 
				m_position.y,
				m_position.z),
			TVertex(0,0,0),
			TVertex(
				CBrush::DEFAULT_SIZE.x, 
				m_size.y,
				m_size.z),
			m_material));
		}

	if ((m_settings & WALL_FRONT) == WALL_FRONT)
		{
		m_walls.push_back(new CBrush(
			TVertex(
				m_position.x, 
				m_position.y + m_size.y/2 + CBrush::DEFAULT_SIZE.z/2,
				m_position.z),
			TVertex(0,0,0),
			TVertex(
				m_size.x, 
				CBrush::DEFAULT_SIZE.y,
				m_size.z),
			m_material));
		}

	if ((m_settings & WALL_REAR) == WALL_REAR)
		{
		m_walls.push_back(new CBrush(
			TVertex(
				m_position.x, 
				m_position.y - m_size.y/2 - CBrush::DEFAULT_SIZE.z/2,
				m_position.z),
			TVertex(0,0,0),
			TVertex(
				m_size.x, 
				CBrush::DEFAULT_SIZE.y,
				m_size.z),
			m_material));
		}

	if ((m_settings & WALL_TOP) == WALL_TOP)
		{
		m_walls.push_back(new CBrush(
			TVertex(
				m_position.x, 
				m_position.y,
				m_position.z + m_size.z/2 + CBrush::DEFAULT_SIZE.z/2),
			TVertex(0,0,0),
			TVertex(
				m_size.x, 
				m_size.y,
				CBrush::DEFAULT_SIZE.z),
			m_material));
		}

		if ((m_settings & WALL_BOTTOM) == WALL_BOTTOM)
		{
		m_walls.push_back(new CBrush(
			TVertex(
				m_position.x, 
				m_position.y,
				m_position.z - m_size.z/2 - CBrush::DEFAULT_SIZE.z/2),
			TVertex(0,0,0),
			TVertex(
				m_size.x, 
				m_size.y,
				CBrush::DEFAULT_SIZE.z),
			m_material));
		}
	}

#if (0)
bool TSMG CRoom::IsWithin(
	const CBrush& p_brush) const
	{
	bool isWithinPos= true;
	int index= 0;
	do
		{
		bool isWithinPos= m_walls[index]->Position() >= p_brush.Position() && p_brush.Position() >= m_position;
		if (isWithinPos)
			{/* check if sides collide */}
		++index;
		}
	while (index <= m_walls.size() && isWithinPos);

	return isWithinPos;
	}
#endif