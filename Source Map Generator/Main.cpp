/*	Main.cpp
 *		Contains the main()!
 *
 */
#include <fstream>
#include <iostream>
#include <string>
#include "Worlds.h"

#include "utils\ClConvertion.h"

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

	CSimple_A myWorld(
		TVertex(1024.0, 1024.0, 128.0),
		seed,
		settings);
	myWorld.Generate();
	
	ofstream oFile("myNewMap." + IntToString(*seed) + ".vmf");
	myWorld.Print(oFile);
	delete seed;

	/*TVertex v(64.0, 64.0, 64.0);
	Translation(v, TVertex(6.0, 6.0, 6.0));
	v;*/

	//CRoom myRoom(TVertex(), TVertex(), TVertex(), "", CRoom::WALL_ALL);
	}