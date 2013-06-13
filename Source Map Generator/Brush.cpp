/*	Brush.cpp
 *
 */
#include <fstream>
#include "Brush.h"
#include "utils/ClConvertion.h"
#include "utils/ClException.h"

using std::string;
using std::ofstream;
using namespace TSMG_NAME;

TVertex TSMG CBrush::DEFAULT_SIZE= TVertex(32.0, 32.0, 32.0);

string TSMG TTextureAxis::ToString() const
	{
	return string(
		"[" + DoubleToString(x) + 
		" " + DoubleToString(y) + 
		" " + DoubleToString(z) + 
		" " + DoubleToString(origin) + 
		"] " + DoubleToString(scale));
	}

TSMG CSide::CSide()
	: CGameObject(TSMG_SIDE_CLASSNAME),
	  m_point1(TVertex()),
	  m_point2(TVertex()),
	  m_point3(TVertex()),
	  m_material(TSMG_SIDE_MATERIAL)
	{}

TSMG CSide::CSide(
	const TVertex& p_point1,
	const TVertex& p_point2,
	const TVertex& p_point3,
	const std::string& p_material)
	: CGameObject(TSMG_SIDE_CLASSNAME),
	  m_point1(p_point1),
	  m_point2(p_point2),
	  m_point3(p_point3),
	  m_material(p_material)
	{
	ExceptionSiVide(m_material);
	}

TSMG CSide::CSide(
	const TVertex& p_point1,
	const TVertex& p_point2,
	const TVertex& p_point3,
	const std::string& p_material,
	const TTextureAxis& p_uAxis,
	const TTextureAxis& p_vAxis)
	: CGameObject(TSMG_SIDE_CLASSNAME),
	  m_point1(p_point1),
	  m_point2(p_point2),
	  m_point3(p_point3),
	  m_material(p_material),
	  m_uAxis(p_uAxis),
	  m_vAxis(p_vAxis)
	{
	ExceptionSiVide(m_material);
	}

TSMG CSide::~CSide()
	{}

const TVertex& TSMG CSide::Point1() const
	{
	return m_point1;
	}

const TVertex& TSMG CSide::Point2() const
	{
	return m_point2;
	}

const TVertex& TSMG CSide::Point3() const
	{
	return m_point3;
	}

const string& TSMG CSide::Material() const
	{
	return m_material;
	}

const TTextureAxis& TSMG CSide::UAxis() const
	{
	return m_uAxis;
	}

const TTextureAxis& TSMG CSide::VAxis() const
	{
	return m_vAxis;
	}


void TSMG CSide::Print(
	std::ofstream& p_oFile) const
	{
	ExceptionSi(p_oFile, !p_oFile.is_open(), "The file could not be opened for writing.");

	p_oFile 
		<< m_className << '\n'
		<< "{\n"
		<< FormatForPrinting("id", IntToString(m_id))
		<< FormatForPrinting("plane", m_point1.ToString() + " " +m_point2.ToString() + " " +m_point3.ToString())
		<< FormatForPrinting("material", m_material)
		//TODO - This part is hardcoded and is to be impleted later.
		<< FormatForPrinting("uaxis", m_uAxis.ToString())
		<< FormatForPrinting("vaxis", m_vAxis.ToString())
		<< FormatForPrinting("rotation", "0")
		<< FormatForPrinting("lightmapscale", "16")
		<< FormatForPrinting("smoothing_groups", "0")
		//END TODO
		<< "}\n";
	}

/////////////////////////

TSMG CBrush::CBrush(
	const TVertex& p_position,	
	const TVertex& p_angles,
	const TVertex& p_size,
	const std::string& p_genericMaterial)	
	: CGameObject(
		TSMG_BRUSH_CLASSNAME,
		p_position, p_angles),
	  m_size(p_size),
	  m_material(p_genericMaterial)
	{
	ExceptionSiVide(m_material);

	m_pVertices= new TVertex[TSMG_BRUSH_VERTICES];
	m_pSides= new CSide[TSMG_BRUSH_SIDES];

	GenerateVertices();
	GenerateSides();
	}

TSMG CBrush::~CBrush()
	{
	delete [] m_pVertices;
	delete [] m_pSides;
	}
	
void TSMG CBrush::GenerateVertices()
	{
	// this is some pretty hardcoding :S
	// is there any way of doing this with matrices?
	m_pVertices[a]= TVertex(
		m_position.x - (m_size.x / 2), 
		m_position.y - (m_size.y / 2), 
		m_position.z + (m_size.z / 2));

	m_pVertices[b]= TVertex(
		m_position.x - (m_size.x / 2), 
		m_position.y + (m_size.y / 2), 
		m_position.z + (m_size.z / 2));

	m_pVertices[e]= TVertex(
		m_position.x - (m_size.x / 2), 
		m_position.y - (m_size.y / 2), 
		m_position.z - (m_size.z / 2));

	m_pVertices[d]= TVertex(
		m_position.x - (m_size.x / 2), 
		m_position.y + (m_size.y / 2), 
		m_position.z - (m_size.z / 2));

	/////

	m_pVertices[g]= TVertex(
		m_position.x + (m_size.x / 2), 
		m_position.y + (m_size.y / 2), 
		m_position.z - (m_size.z / 2));

	m_pVertices[f]= TVertex(
		m_position.x + (m_size.x / 2), 
		m_position.y - (m_size.y / 2), 
		m_position.z - (m_size.z / 2));

	m_pVertices[c]= TVertex(
		m_position.x + (m_size.x / 2), 
		m_position.y + (m_size.y / 2), 
		m_position.z + (m_size.z / 2));

	m_pVertices[h]= TVertex(
		m_position.x + (m_size.x / 2), 
		m_position.y - (m_size.y / 2), 
		m_position.z + (m_size.z / 2));
	}

void TSMG CBrush::GenerateSides()
	{
	// another hardcoding batch here too :O
	// yet again, matrices?
	//TODO - Optimize the u/v axes instead of hard coding them
	m_pSides[0]= CSide(m_pVertices[a], m_pVertices[b], m_pVertices[c], m_material, TTextureAxis(1.0, 0.0, 0.0, 0.0, 0.25), TTextureAxis(0.0, -1.0, 0.0, 0.0, 0.25));
	m_pSides[1]= CSide(m_pVertices[d], m_pVertices[e], m_pVertices[f], m_material, TTextureAxis(1.0, 0.0, 0.0, 0.0, 0.25), TTextureAxis(0.0, -1.0, 0.0, 0.0, 0.25));
	m_pSides[2]= CSide(m_pVertices[e], m_pVertices[d], m_pVertices[b], m_material, TTextureAxis(0.0, 1.0, 0.0, 0.0, 0.25), TTextureAxis(0.0, 0.0, -1.0, 0.0, 0.25));
	m_pSides[3]= CSide(m_pVertices[g], m_pVertices[f], m_pVertices[h], m_material, TTextureAxis(0.0, 1.0, 0.0, 0.0, 0.25), TTextureAxis(0.0, 0.0, -1.0, 0.0, 0.25));
	m_pSides[4]= CSide(m_pVertices[d], m_pVertices[g], m_pVertices[c], m_material, TTextureAxis(1.0, 0.0, 0.0, 0.0, 0.25), TTextureAxis(0.0, 0.0, -1.0, 0.0, 0.25));
	m_pSides[5]= CSide(m_pVertices[f], m_pVertices[e], m_pVertices[a], m_material, TTextureAxis(1.0, 0.0, 0.0, 0.0, 0.25), TTextureAxis(0.0, 0.0, -1.0, 0.0, 0.25));
	}

void TSMG CBrush::Print(
	std::ofstream& p_oFile) const
	{
	ExceptionSi(p_oFile, !p_oFile.is_open(), "The file could not be opened for writing.");

	p_oFile 
		<< m_className << '\n'
		<< "{\n"
		<< FormatForPrinting("id", IntToString(m_id));
	
	for (int i= 0; i != TSMG_BRUSH_SIDES; ++i)
		m_pSides[i].Print(p_oFile);

	p_oFile
		// Useless block..
		<< "editor\n"
		<< "{\n"
		<< FormatForPrinting("color", "0 173 254")
		<< FormatForPrinting("visgroupshown", "1")
		<< FormatForPrinting("visgroupautoshown", "1")
		<< "}\n"
		// End useless block
		<< "}\n";
	}

const TVertex& TSMG CBrush::Size() const
	{
	return m_size;
	}