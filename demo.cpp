#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
using namespace std;

#define PI 3.14159f
#define DEG_TO_RAD PI/180.f

struct vec3d
{
    float x, y, z;
};
struct triangle
{
    vec3d t_point[3];
};
struct mesh
{
    vector<triangle> tris;
};
struct mat4x4
{
    float m[4][4] = {0};
};

// Override base class with your custom functionality
class Engine3D : public olc::PixelGameEngine
{
public:
	Engine3D()
	{
		// Name your application
		sAppName = "3DEngine Cube";
	}

private:
    mesh meshCube;
    mat4x4 matProj;

    void VecMatMult(vec3d &i, vec3d &o, mat4x4 &m)
    {
        o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
		o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
		o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
		float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

		if (w != 0.0f)
		{
			o.x /= w; o.y /= w; o.z /= w;
		}
    }

public:
	bool OnUserCreate() override
	{
		meshCube.tris = {
        // SOUTH
		{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		// EAST                                                      
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

		// NORTH                                                     
		{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

		// WEST                                                      
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

		// TOP                                                       
		{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

		// BOTTOM                                                    
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },

        };

        float fNear = 0.1f;
        float fFar = 1000.0f;
        float fFov = 90.0f;
        float fAspectRatio = (float)ScreenHeight()/(float)ScreenWidth();
        float fFovRad = 1.0f / tanf(fFov * 0.5f * DEG_TO_RAD);

        matProj.m[0][0] = fAspectRatio * fFovRad;
        matProj.m[1][1] = fFovRad;
        matProj.m[2][2] = fFar / (fFar - fNear);
        matProj.m[3][2] = -fFar*fNear / (fFar - fNear);
        matProj.m[2][3] = 1.0f;
        matProj.m[3][3] = 0.0f;

		return true;
	}

    void FillBlack(void)
    {
        // Called once per frame, draws black pixels
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel((uint8_t)0, (uint8_t)0, (uint8_t)0));
    }

	bool OnUserUpdate(float fElapsedTime) override
	{
		FillBlack();

                for(auto tri : meshCube.tris)
        {
            triangle triProjected;
            for(int idx=0;idx<3;idx++)
            {
                VecMatMult(tri.t_point[idx], triProjected.t_point[idx], matProj);
            }

            DrawTriangle(
                triProjected.t_point[0].x, triProjected.t_point[0].y,
                triProjected.t_point[1].x, triProjected.t_point[1].y,
                triProjected.t_point[2].x, triProjected.t_point[2].y
                );

        }

		return true;
	}
};

int main()
{
	Engine3D demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
	return 0;
}
