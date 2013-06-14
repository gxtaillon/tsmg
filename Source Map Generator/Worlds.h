/*	Worlds.h
 *
 */
#pragma once
#include <vector>
#include "Room.h"

#define TSMG_WORLD_CLASSNAME					"worldspawn"
#define TSMG_WORLD_DESIGNATION					"world"


TSMG_BEGIN

struct TWorldSettings :	// should be within CBaseWorld
	public CBaseObject
	{
	int maxBrushes,	minBrushes;
	TSMG_NIMP int maxProps, minProps;
	TSMG_NIMP TVertex maxBrushSize, minBrushSize;

	TWorldSettings()
		: maxBrushes(1), minBrushes(0),
		  maxProps(1), minProps(0),
		  maxBrushSize(CBrush::DEFAULT_SIZE), minBrushSize(CBrush::DEFAULT_SIZE)
		{}

	TWorldSettings(const TWorldSettings& p_instance)
		: maxBrushes(p_instance.maxBrushes), minBrushes(p_instance.minBrushes),
		  maxProps(p_instance.maxProps), minProps(p_instance.minProps),
		  maxBrushSize(p_instance.maxBrushSize), minBrushSize(p_instance.minBrushSize)
		{}
	};

class CBaseWorld :
	public CGameObject
	{
	public:
		/*virtual*/ void Print(
			std::ofstream& p_oFile) const;

		CBaseWorld(
			const TVertex& p_size,
			const int* p_seed,
			const TWorldSettings& p_worldSettings);

		~CBaseWorld();

		void Generate();				// template method!

		virtual void Prepare()	{};		// create the skybox, ground, etc.
		virtual void Create()	{};		// walls, rooms, etc.
		virtual void Finalize()	{};		// lights, props, etc.

	protected:
		TWorldSettings m_worldSettings;
		TVertex m_size;
		const int* m_cSeed;
		std::vector<CGameObject*> m_objects;
	};


class CSimple_A :											
	public CBaseWorld									
	{													
	public:												
		CSimple_A(											
			const TVertex& p_size,						
			const int* p_seed,							
			const TWorldSettings& p_worldSettings);		

		~CSimple_A();									

	private:											
		/*virtual*/ void Prepare();						
		/*virtual*/ void Create();						
		/*virtual*/ void Finalize();					
		};

class CCluster_A :											
	public CBaseWorld									
	{													
	public:												
		CCluster_A(											
			const TVertex& p_size,						
			const int* p_seed,							
			const TWorldSettings& p_worldSettings);		

		~CCluster_A();									

	private:											
		/*virtual*/ void Prepare();						
		/*virtual*/ void Create();						
		/*virtual*/ void Finalize();					
		};


class CComplex_A :											
	public CBaseWorld									
	{													
	public:												
		CComplex_A(											
			const TVertex& p_size,						
			const int* p_seed,							
			const TWorldSettings& p_worldSettings);		

		~CComplex_A();		

	private:											
		/*virtual*/ void Prepare();						
		/*virtual*/ void Create();						
		/*virtual*/ void Finalize();

		int TSMG_RECURSIVE PerambulateTheMaze(		
			const int p_currentCellIndex,
			const int p_previousCellIndex);

		inline int Index(
			const int p_x,
			const int p_y)
			{	return Array2DIndex(p_x, p_y, m_gridWidth);	}

		inline int RIndexX(
			const int p_index)
			{	return Array2DReverseIndexX(p_index, m_gridWidth);	}

		inline int RIndexY(
			const int p_index)
			{	return Array2DReverseIndexY(p_index, m_gridWidth);	}

		int m_gridWidth;
		int m_gridHeight;
		};

TSMG_END