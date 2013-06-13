/*	Types.cpp
 *
 */
#include "Types.h"
#include "utils/ClConvertion.h"

using std::string;
using namespace TSMG_NAME;


int TSMG Array2DIndex(
	const int p_x, 
	const int p_y, 
	const int p_count)
	{
	if (p_x >= p_count)
		return -1;

	return p_y * p_count + p_x;
	}

int TSMG Array2DReverseIndexX(
	const int p_index,
	const int p_count)
	{
	return p_index % p_count;
	}

int TSMG Array2DReverseIndexY(
	const int p_index,
	const int p_count)
	{
	return (p_index - Array2DReverseIndexX(p_index, p_count)) / p_count;
	}

double Random(
	const double& p_minimum,
	const double& p_maximum)
	{
    return ((double)rand() / (double)RAND_MAX) * (p_maximum - p_minimum) + p_minimum;
	}


std::string TSMG TVertex::ToString() const
	{
	return string("(" 
		+ DoubleToString(x) + " " 
		+ DoubleToString(y) + " " 
		+ DoubleToString(z) + ")");
	}

double& TSMG TVertex::operator[](
	const short& p_index)
	{
	//ExceptionSi(p_index, 0 > p_index || p_index > 2, "Out of bounds");
	switch (p_index)
		{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		default: throw ExceptionEnregistree("Out of bounds");
		}
	}

const double& TSMG TVertex::operator[](
	const short& p_index) const
	{
	//ExceptionSi(p_index, 0 > p_index || p_index > 2, "Out of bounds");
	switch (p_index)
		{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		default: throw ExceptionEnregistree("Out of bounds");
		}
	}


void TSMG Transformations3D::Translation(
		TVertex& p_origin,
		const TVertex& p_offset)
		{
		CMatrix matrix;

		matrix[0][0]= 1;
		matrix[1][1]= 1;
		matrix[2][2]= 1;
		matrix[3][3]= 1;

		matrix[3][0]= p_offset.x;
		matrix[3][1]= p_offset.y;
		matrix[3][2]= p_offset.z;

		p_origin.Multiply(matrix);
		}