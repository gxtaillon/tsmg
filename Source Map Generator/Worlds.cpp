/*	Worlds.cpp
 *
 */
#include <fstream>
#include <algorithm>
#include <time.h>
#include "Worlds.h"
#include "utils/ClException.h"
#include "utils/ClConvertion.h"

using namespace TSMG_NAME;
using namespace std;


////////////////////
// BASEWORLD
////////////////////
TSMG CBaseWorld::CBaseWorld(
	const TVertex& p_size,
	const int* p_seed,
	const TWorldSettings& p_worldSettings)
	: CGameObject(
		TSMG_WORLD_CLASSNAME,
		TVertex(), TVertex()),
	  m_size(p_size),
	  m_cSeed(p_seed),
	  m_worldSettings(p_worldSettings)
	{
	srand( (m_cSeed == NULL) ? time(NULL) : *m_cSeed );
	}

TSMG CBaseWorld::~CBaseWorld()
	{
	for (int i= m_objects.size() - 1; i >= 0; --i)
		{
		delete m_objects[i];
		m_objects.pop_back();
		}
	}

void TSMG CBaseWorld::Generate()
	{
	Prepare();
	Create();
	Finalize();
	}

void TSMG CBaseWorld::Print(
	std::ofstream& p_oFile) const
	{
	ExceptionSi(p_oFile, !p_oFile.is_open(), "The file could not be opened for writing.");

	// header 
	p_oFile
		// Useless block
		<< "versioninfo {\n"
		<< FormatForPrinting("editorversion", "400")
		<< FormatForPrinting("editorbuild", "5004")
		<< FormatForPrinting("mapversion", "1")
		<< FormatForPrinting("formatversion", "100")
		<< FormatForPrinting("prefab", "0")
		<< "}\n"
		<< "visgroups {}\n"
		<< "viewsettings {\n"
		<< FormatForPrinting("bSnapToGrid", "1")
		<< FormatForPrinting("bShowGrid", "1")
		<< FormatForPrinting("bShowLogicalGrid", "0")
		<< FormatForPrinting("nGridSpacing", "32")
		<< FormatForPrinting("bShow3DGrid", "0")
		<< "}\n"
		// This is getting more interesting
		<< TSMG_WORLD_DESIGNATION << " {\n"
		<< FormatForPrinting("id",				IntToString(m_id))
		<< FormatForPrinting("mapversion",		"1")
		<< FormatForPrinting("classname",		TSMG_WORLD_CLASSNAME)
		<< FormatForPrinting("detailmaterial",	"detail/detailsprites")
		<< FormatForPrinting("detailvbsp",		"detail.vbsp")
		<< FormatForPrinting("maxpropscreenwidth", "-1")
		<< FormatForPrinting("skyname",			"sky_day01_01");
		
	for (int i= 0; i != m_objects.size(); ++i)
		m_objects[i]->Print(p_oFile);

	// footer
	p_oFile
		<< "}\n";
	}


////////////////////
// CLUSTER A
////////////////////
TSMG CCluster_A::CCluster_A(									
	const TVertex& p_size,								
	const int* p_seed,									
	const TWorldSettings& p_worldSettings)				
	: CBaseWorld(										
		p_size,											
		p_seed,											
		p_worldSettings)								
	{}													
														
TSMG CCluster_A::~CCluster_A()									
	{}

void TSMG CCluster_A::Prepare()
	{
	// Let's be simple and wrap the map in a skybox.
	m_objects.push_back(new CRoom(
		TVertex(),
		TVertex(),
		m_size,
		"tools/toolsskybox",
		CRoom::WALL_ALL));

	// Generate a floor near the bottom, with some walls to prevent falling
	m_objects.push_back(new CRoom(
		TVertex(
			0.0,
			0.0,
			-m_size.z * 0.15),
		TVertex(),
		TVertex(
			m_size.x * 0.9,
			m_size.y * 0.9,
			m_size.z * 0.15),
		"dev/dev_measuregeneric01",
		CRoom::WALL_ALL ^ CRoom::WALL_TOP));
	}

void TSMG CCluster_A::Create()
	{
	int qtyBrushes= rand() % m_worldSettings.maxBrushes + m_worldSettings.minBrushes;
	TVertex prev= CBrush::DEFAULT_SIZE;
	CBrush::DEFAULT_SIZE= TVertex(64.0, 64.0, m_size.z * 0.15);

	for (int i= 0; i != qtyBrushes; ++i)
		{
		m_objects.push_back(new CBrush(
			TVertex( // l3t's tr0ll
				static_cast<double>(rand() % static_cast<int>(m_position.x + m_size.x/* - (CBrush::DEFAULT_SIZE.x * 2)*/)) - (m_position.x/2 + m_size.x/2/* + (CBrush::DEFAULT_SIZE.x * 2)*/),
				static_cast<double>(rand() % static_cast<int>(m_position.y + m_size.y/* - (CBrush::DEFAULT_SIZE.y * 2)*/)) - (m_position.y/2 + m_size.y/2/* + (CBrush::DEFAULT_SIZE.y * 2)*/),
				-m_size.z * 0.15),
			TVertex(),
			CBrush::DEFAULT_SIZE,
			"dev/dev_measuregeneric01b"));				
		}

	CBrush::DEFAULT_SIZE= prev;
	}

void TSMG CCluster_A::Finalize()
	{}


////////////////////
// COMPLEX A
////////////////////
TSMG CComplex_A::CComplex_A(									
	const TVertex& p_size,								
	const int* p_seed,									
	const TWorldSettings& p_worldSettings)				
	: CBaseWorld(										
		p_size,											
		p_seed,											
		p_worldSettings),
	  m_gridWidth(static_cast<int>(m_size.x/64)),
	  m_gridHeight(static_cast<int>(m_size.y/64))
	{
	ExceptionSi(m_size, 64 > m_size.x || 64 > m_size.y, "The size must be at least of 64 for x and y.");

	int size= m_gridHeight * m_gridWidth;
	m_objects= vector<CGameObject*>(size);
	for (int i= 0; i != size; ++i)
		m_objects[i]= new CRoom();
	}													
														
TSMG CComplex_A::~CComplex_A()									
	{}

void TSMG CComplex_A::Prepare()
	{
	PerambulateTheMaze(0, -1);
	}

void TSMG CComplex_A::Create()
	{

	}

void TSMG CComplex_A::Finalize()
	{
	}

// this function implements the depth-first search algorithm. (http://en.wikipedia.org/wiki/Maze_generation_algorithm#Depth-first_search)
int TSMG_RECURSIVE TSMG CComplex_A::PerambulateTheMaze(		
	const int p_currentCellIndex,
	const int p_previousCellIndex)
	{
	/*if (p_previousCellIndex == -1)
		m_objects[p_currentCellIndex]*/

	vector<int> neighbors;
	int x= RIndexX(p_currentCellIndex);
	int y= RIndexY(p_currentCellIndex);

	// gets the neightbors...
	/*
	N: A neightbor
	C: The current cell
	.: We dont care about that cell...
	<integer>: the index of the cell

	Example:
		3x3 grid
		current cell index's = 4
		possible neightbors are : 1, 3, 5, 7

	Y
	2	. 6	|	N 7	|	. 8
		----+-------+----
	1	N 3	|	C 4	|	N 5
		----+-------+----
	0	. 0	|	N 1	|	. 2

		0		1		2 X
	*/
	if (x - 1 > 0)
		neighbors.push_back(Index(x - 1, y));

	if (x + 1 < m_gridWidth)
		neighbors.push_back(Index(x + 1, y));

	if (y - 1 > 0)
		neighbors.push_back(Index(x, y - 1));

	if (y + 1 < m_gridHeight)
		neighbors.push_back(Index(x, y + 1));

	// we reached the end of this branch
	if (neighbors.empty())
		return -1;

	random_shuffle(neighbors.begin(), neighbors.end());
	for (int i= 0; i != neighbors.size(); ++i)
		{
		
		}
	}