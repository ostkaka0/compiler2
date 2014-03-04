#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>

#define WIDTH 512//0-256
#define HEIGHT 240//80-240
#define PI 3.14159265358979

struct Block;
Block Create(unsigned char b, unsigned char g, unsigned char r);

Block ***world;//[WIDTH*WIDTH][HEIGHT];

std::vector<unsigned char> **raw;

struct Block
{
	unsigned char Blue;
	unsigned char Green;
	unsigned char Red;
	//unsigned char T;
};

int main()
{
	world = new Block**[WIDTH];
	raw = new std::vector<unsigned char>*[WIDTH];

	for (int x = 0; x < WIDTH; x++)
	{
		std::cout << "x: "<< x << std::endl;

		world[x] = new Block*[WIDTH];
		raw[x] = new std::vector<unsigned char>[WIDTH];
		for (int y = 0; y < WIDTH; y++)
		{
			world[x][y] = (Block*)malloc(4*HEIGHT);//new Block[HEIGHT];
			//raw[x][y] = new unsigned char[WIDTH];

			for (int z = 0; z < HEIGHT; z++)
			{
				double distance = sqrt(pow((double)(x-WIDTH/2),2)	+	pow((double)(y-WIDTH/2),2)	+	pow((double)(z-HEIGHT/2),2));

				world[x][y][z] = (((
					sin(distance*PI/((double)HEIGHT/8.0)) > 0 &&
					distance < HEIGHT-16&&false)||(z == 0))? Create(192,64,32):Create(0,0,0));
			}

			unsigned char distanceToGap = 0;
			unsigned char airEnd = 0;
			unsigned char lastSolidEnd = HEIGHT-1;
			bool air = false;
			std::vector<unsigned char> data;

			for (int z = HEIGHT-1; z >= 0; z--)
			{
				if (world[x][y][z].Blue == 0 && z != 0)
				{
					if (air)
					{
						continue;
					}
					else
					{
						airEnd = z;
						air = true;
						continue;
					}
				}
				else
				{
					bool solid = (world[x][y][z].Blue != 0);

					if (solid || distanceToGap == HEIGHT-1)
					{
						data.push_back((unsigned char)0x7F);
						data.push_back(world[x][y][z].Red);
						data.push_back(world[x][y][z].Green);
						data.push_back(world[x][y][z].Blue);
					}
					
					if (air)
					{
						
						data.push_back((z == 0)? 0:((unsigned char)z+1));
						data.push_back((solid)? lastSolidEnd-1:lastSolidEnd);
						data.push_back((solid)? lastSolidEnd-1:lastSolidEnd);
						data.push_back(distanceToGap);

						distanceToGap = 0;
						//lastSolidEnd = z;
						air = false;
					}

					if (solid)
					lastSolidEnd = z;//?
					

				}
				distanceToGap++;
			}

			//data.insert(data.begin(), (unsigned char)data.size());

			raw[x][y] = data;
			//raw[x][y]->getArray(&data[0]);


			delete world[x][y];
		}
		delete world[x];
	}
	std::filebuf fb;
	fb.open("Custommap_11 - Kopia.vxl", std::ios::out);

	std::ostream output(&fb);

	/*output << (unsigned int)0x09072000 << (unsigned int)WIDTH << (unsigned int)HEIGHT;

	for ( int i = 0 ; i < 12; i++)
	{
		output << (double)0.0;
	}*/
		/*
		header:
			{
				uint32 magic = 0x09072000
				uint32 width;
				uint32 height;

				[dpoint3d] ip, ist, ihe, ifo
			}

			dpoint3d:
			{
				double x,y,z;
			}
		*/

	for (int x = 0; x < WIDTH; x++)
	{
		std::cout << "x: "<< x << std::endl;
		for (int y = 0; y < WIDTH; y++)
		{
			//std::cout << (int)raw[x][y].size() << std::endl;
			//output << raw[x][y];
			for (int z = raw[x][y].size()-1; z >= 0; z--)
			{
				output << raw[x][y][z];
			}
			/*for (int z = 0; z < HEIGHT; z++)
			{

			}*/
		}
	}

	fb.close();

	return 0;
}



Block Create(unsigned char b, unsigned char g, unsigned char r)
{
	Block bl;

	bl.Blue = b;
	bl.Green = g;
	bl.Red = r;

	return bl;
}