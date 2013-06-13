/*	Room.h
 *
 */
#pragma once
#include <vector>
#include "Brush.h"

#define TSMG_ROOM_CLASSNAME	"TSMG_room"
#define TSMG_ROOM_MATERIAL	"tools/nodraw"

TSMG_BEGIN

class CRoom :
	public CGameObject
	{
	public:
		CRoom();

		CRoom(
			const TVertex& p_position,			// point of origin (exact center)
			TSMG_NIMP const TVertex& p_angles,	// amount of degrees in x,y,z to rotate
			const TVertex& p_size,				// from x/z view: x= width, y= depth, z= height of the room's interior
			const std::string& p_genericMaterial,
			const unsigned short p_settings);

		~CRoom();

		/*virtual*/ void Print(
			std::ofstream& p_oFile) const;

		bool IsWithin(
			const CBrush& p_brush) const;

		void Settings(
			const unsigned short p_settings);
		unsigned short Settings() const;

		enum ESettings
			{
			WALL_LEFT=		(1),
			WALL_RIGHT=		(1 << 1),
			WALL_FRONT=		(1 << 2),
			WALL_REAR=		(1 << 3),
			WALL_TOP=		(1 << 4),
			WALL_BOTTOM=	(1 << 5),
			WALL_ALL= WALL_LEFT | WALL_RIGHT | WALL_FRONT | WALL_REAR | WALL_TOP | WALL_BOTTOM
			};

	protected:
		void GenerateWalls();

		std::vector<CBrush*> m_walls;
		TVertex m_size;
		std::string m_material;
		unsigned short m_settings;
	};

TSMG_END