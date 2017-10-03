#pragma once

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>

#ifndef PI
#define PI 3.14159265358979f
#endif

// TODO: Use quaternions

class Camera {
public:
	// PITCH, YAW, and ROLL are aliases
	static const glm::vec3 X_AXIS, &PITCH;
	static const glm::vec3 Y_AXIS, &YAW;
	static const glm::vec3 Z_AXIS, &ROLL;
private:
	static float yaw, pitch, roll;
	static glm::vec3 position;
public:
	static glm::mat4 GetViewMatrix();
	static glm::vec3 GetPosition();
	static glm::vec3 GetFront();
	static glm::vec3 GetUp();
	static glm::vec3 GetRight();
	static float GetRoll();
	static float GetPitch();
	static float GetYaw();
	static float GetX();
	static float GetY();
	static float GetZ();
	static void RotateRoll(float angle);
	static void RotatePitch(float angle);
	static void RotateYaw(float angle);
	static void SetRoll(float angle);
	static void SetPitch(float angle);
	static void SetYaw(float angle);
	static void SetX(float x);
	static void SetY(float y);
	static void SetZ(float z);
	static void Move(glm::vec3 displacement);
	static void Rotate(glm::vec3 axis, float angle);
	static void SetRotation(float yaw, float pitch, float roll);
	static void SetPosition(float x, float y, float z);
	static void Reset();
};
