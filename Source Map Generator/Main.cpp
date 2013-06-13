/*	Main.cpp
 *		Contains the main()!
 *
 */
#include <fstream>
#include <iostream>
#include <string>
#include "Worlds.h"

#include <ctime>
using namespace std;
using namespace TSMG_NAME;
using namespace Transformations3D;

/*ofstream& OFileHandler(
	const string& p_fileName,
	const string& p_extension)
	{
	// boost filesystem calls instead of os specific ones for increased portability :D
	return;
	}*/

int main(int argc, char* argv[])
	{
	srand(time(NULL));

	TWorldSettings settings;
	settings.maxBrushes= 70;
	settings.minBrushes= 20;
	int* seed= new int();
	*seed= rand();

	CComplex_A myWorld(
		TVertex(2560.0, 2560.0, 128.0),
		seed,
		settings);
	myWorld.Generate();
	
	delete seed;
	ofstream oFile("myNewMap.vmf");
	myWorld.Print(oFile);

	/*TVertex v(64.0, 64.0, 64.0);
	Translation(v, TVertex(6.0, 6.0, 6.0));
	v;*/

	CRoom myRoom(TVertex(), TVertex(), TVertex(), "", CRoom::WALL_ALL);
	}