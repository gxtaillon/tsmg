/*	Brush.h
 *		{CBrush} is, like its name says, a brush. It is used to create 
 *		walls, floors and ceilings. A brush has six (6) {CSide}. This 
 *		limit simplify calculations, since everything can be 
 *		made out of hexahedrons. Note that {CBrush} can only create 
 *		rectangular cuboids (square prisms).
 *
 */
#pragma once
#include <string>
#include "GameObject.h"

#define TSMG_SIDE_CLASSNAME	"side"
#define TSMG_SIDE_MATERIAL	"TOOLS/TOOLSNODRAW"
#define TSMG_BRUSH_CLASSNAME	"solid"
#define TSMG_BRUSH_SIDES		6
#define TSMG_BRUSH_VERTICES	8

TSMG_BEGIN

struct TTextureAxis :
	public TVertex
	{
	double origin, scale;


	TTextureAxis()
		: TVertex(),
		  origin(0.0),
		  scale(0.0)
		{}

	TTextureAxis(
		const double& p_x,
		const double& p_y,
		const double& p_z,
		const double& p_origin,
		const double& p_scale)
		: TVertex(p_x, p_y, p_z),
		  origin(p_origin),
		  scale(p_scale)
		{}

	/*virtual*/ std::string ToString() const;
	};

class CSide :
	public CGameObject
	{
	public:
		CSide();
		CSide(
			const TVertex& p_point1,
			const TVertex& p_point2,
			const TVertex& p_point3,
			const std::string& p_material);
		CSide(
			const TVertex& p_point1,
			const TVertex& p_point2,
			const TVertex& p_point3,
			const std::string& p_material,
			const TTextureAxis& p_uAxis,
			const TTextureAxis& p_vAxis/*,
			const double& p_rotation,
			const long& p_lightMapScale,
			const long& p_smoothingGroup*/);
		~CSide();

		const TVertex& Point1() const;
		const TVertex& Point2() const;
		const TVertex& Point3() const;
		const std::string& Material() const;
		const TTextureAxis& CSide::UAxis() const;
		const TTextureAxis& CSide::VAxis() const;

		/*virtual*/ void Print(
			std::ofstream& p_oFile) const;

	private:
		TVertex m_point1;
		TVertex m_point2;
		TVertex m_point3;
		std::string m_material;

		TTextureAxis m_uAxis;
		TTextureAxis m_vAxis;
		/*double m_rotation;
		long m_lightMapScale;
		long m_smoothingGroups;*/
	};

class CBrush :
	public CGameObject
	{
	public:
		CBrush(
			const TVertex& p_position,			// point of origin (exact center)
			TSMG_NIMP const TVertex& p_angles,	// amount of degrees in x,y,z to rotate
			const TVertex& p_size,				// from x/z view: x= width, y= depth, z= height
			const std::string& p_genericMaterial);		
		~CBrush();

		/*virtual*/ void Print(
			std::ofstream& p_oFile) const;

		const TVertex& Size() const;

		static TVertex DEFAULT_SIZE;

	protected:
		void GenerateSides();
		void GenerateVertices();

		enum EJoints
			{
			a= 0, b, c, d, e, f, g, h
			};

		TVertex* m_pVertices;
		CSide* m_pSides;
		TVertex m_size;
		std::string m_material;
	};

TSMG_END