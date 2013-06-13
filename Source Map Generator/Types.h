/*	Types.h
 *
 */
#pragma once
#include <cmath>
#include <string>
#include "BaseObject.h"
#include "utils/ClException.h"


TSMG_BEGIN

// accesses the element at [X,Y] in the array knowing how much element each row contains. Returns the index.
int Array2DIndex(
	const int p_x, 
	const int p_y, 
	const int p_count);

// IDEM RINDEXY except it returns X.
int Array2DReverseIndexX(
	const int p_index,
	const int p_count);

// reverse index of Y knowing the index and how much elements each row contains. Returns Y.
int Array2DReverseIndexY(
	const int p_index,
	const int p_count);

// Returns a random number between the given boundaries.
double Random(
	const double& p_minimum,
	const double& p_maximum);


class CMatrix44
	{
	public:
		class CColumns
			{
			public:
				CColumns()
					{
					pRows= new double[4];
					}

				~CColumns()
					{
					delete [] pRows;
					}

				double& operator[](
					const unsigned short& p_index)
					{
					ExceptionSi(p_index, 0 > p_index || p_index > 3, "Out of bounds");
					return pRows[p_index];
					}

				const double& operator[](
					const unsigned short& p_index) const
					{
					ExceptionSi(p_index, 0 > p_index || p_index > 3, "Out of bounds");
					return pRows[p_index];
					}
				
				double* pRows;
			};

		CMatrix44()
			{
			pColumns= new CColumns[4];
			for(int i= 0; i != 3; ++i)
				for(int j= 0; j != 3; ++j)
					pColumns[i][j]= 0.0;
			}

		~CMatrix44()
			{
			delete [] pColumns;
			}

		CColumns& operator[](
			const unsigned short& p_index)
			{
			//ExceptionSi(p_index, 0 > p_index || p_index > 3, "Out of bounds");
			return pColumns[p_index];
			}

		const CColumns& operator[](
			const unsigned short& p_index) const
			{
			//ExceptionSi(p_index, 0 > p_index || p_index > 3, "Out of bounds");
			return pColumns[p_index];
			}

		CMatrix44& Multiply(
			const CMatrix44& p_matrix)
			{
			for(int i= 0; i != 3; ++i)
				for(int j= 0; j != 3; ++j)
					for(int k= 0; k != 3; k++)
						pColumns[i][j]+= pColumns[i][k] * p_matrix[k][j];

			return *this;
			}

		CColumns* pColumns;
	};

typedef CMatrix44 CMatrix;


struct TVertex :
	public CBaseObject
	{
	double x, y, z;

	TVertex()
		: x(0.0),
		  y(0.0),
		  z(0.0)
		{}

	TVertex(
		const double& p_x,
		const double& p_y,
		const double& p_z)
		: x(p_x),
		  y(p_y),
		  z(p_z)
		{}

	double& operator[](
		const short& p_index);

	const double& operator[](
		const short& p_index) const;

	virtual std::string ToString() const;

	TVertex& Multiply(
		const CMatrix44& p_matrix)
		{
		for (int i= 0; i != 2; ++i)
			{
			double buffer= 0.0;
			int j;
			for (j= 0; j != 2; ++j)
				buffer+= (*this)[j] * p_matrix[i][j];
			buffer+= p_matrix[i][++j]; // <<<<------------------

			(*this)[i]= buffer;
			}

		return *this;
		}
	};

namespace Transformations3D
{
	void Translation(
		TVertex& p_origin,
		const TVertex& p_offset);
}

TSMG_END