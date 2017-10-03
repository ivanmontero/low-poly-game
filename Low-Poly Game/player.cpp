#include "player.h"
#include "camera.h"

int Player::x = 0;
int Player::y = 0;
int Player::z = 0;

void Player::RotateCamera(float mdx, float mdy) {
	Camera::RotatePitch(mdy * sensitivity);
	Camera::RotateYaw(mdx * sensitivity);

	if (Camera::GetPitch() > PI / 2.0f - 0.01f) Camera::SetPitch(PI / 2.0f - 0.01f);
	if (Camera::GetPitch() < -PI / 2.0f + 0.01f) Camera::SetPitch(-PI / 2.0f + 0.01f);
}

void Player::Move(int dx, int dy, int dz) {
	x += dx;
	y += dy;
	z += dz;
}
