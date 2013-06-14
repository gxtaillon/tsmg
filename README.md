tsmg
====

Typhoon Source Map Generator
It's an old project I did during the summer of 2011. It's unfinished but I found it in my archives and I tought maybe someone could have fun with it.

What it intended to do was to provide objects to create the various parts of the VMF file format, allowing the creation of prefabs and maps by the push of a button. What has been implemented are the components of brushes and another construct I called a Room. Rooms are simply 6 brushes, one for each side. There are also unfinished experiments like the CComplex_A world type. 

Exemple:
To create a map, derive a new type from CBaseWorld. There are 3 methods you may override in CBaseWorld, Prepare(), Create() and Finalize(). They will be called in this order when the world is generated.
```
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
```
To actually add objects to a world, push them into the world's m_objects vector. The following code creates a platform inside a slightly larger skybox centered on the origin.
```
// Let's be simple and wrap the map in a skybox.
m_objects.push_back(new CRoom(
    TVertex(),            // point of origin (exact center)
    TVertex(),            // Not implemented, amount of degrees in x,y,z to rotate
    m_size,               // from x/z view: x= width, y= depth, z= height of the room's interior
    "tools/toolsskybox",  // material used to texture the walls of the room
    CRoom::WALL_ALL));    // sides that must be created. The flags are (WAll_~, LEFT, RIGHT, FRONT, REAR, TOP, BOTTOM, ALL).

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
```    

Note: I am reading my code as I type this readme and I can say that some design choices are now mysterious to me.