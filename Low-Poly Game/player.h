#pragma once

static float sensitivity = 0.0025f;

class Player {
public:
	static int x, y, z;

	static void RotateCamera(float mdx, float mdy);
	static void Move(int dx, int dy, int dz);
};