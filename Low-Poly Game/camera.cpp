#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

// TODO: Use quaternions, and make member variables public

const glm::vec3		Camera::X_AXIS		= glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3		Camera::Y_AXIS		= glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3		Camera::Z_AXIS		= glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3&	Camera::PITCH		= Camera::X_AXIS;	// Alias
const glm::vec3&	Camera::YAW			= Camera::Y_AXIS;	// Alias
const glm::vec3&	Camera::ROLL		= Camera::Z_AXIS;	// Alias

glm::vec3			Camera::position	= glm::vec3();
float				Camera::roll		= 0.0f;
float				Camera::pitch		= 0.0f;
float				Camera::yaw			= 0.0f;

#define				PI					3.14159265358979f

glm::mat4 Camera::GetViewMatrix() { return glm::lookAt(position, position + GetFront(), GetUp()); }

glm::vec3 Camera::GetPosition() { return position; }

glm::vec3 Camera::GetFront(){ return (glm::yawPitchRoll(yaw, pitch, roll) * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f)).xyz(); }

glm::vec3 Camera::GetUp(){ return (glm::yawPitchRoll(yaw, pitch, roll) * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)).xyz(); }

glm::vec3 Camera::GetRight(){ return (glm::yawPitchRoll(yaw, pitch, roll) * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)).xyz(); }

float Camera::GetRoll() { return roll > PI ? roll - 2 * PI : roll; }	// Z axis

float Camera::GetPitch(){ return pitch > PI ? pitch - 2*PI : pitch;}	// X axis

float Camera::GetYaw() { return yaw > PI ? yaw - 2 * PI : yaw; }	// Y axis

float Camera::GetX() { return position.x; }

float Camera::GetY() { return position.y; }

float Camera::GetZ() { return position.z; }

void Camera::RotateRoll(float angle) { roll = glm::mod(roll + angle, 2 * PI); }

void Camera::RotatePitch(float angle) {	pitch = glm::mod(pitch + angle, 2 * PI); }

void Camera::RotateYaw(float angle) { yaw = glm::mod(yaw + angle, 2 * PI); }

void Camera::SetRoll(float angle) { roll = angle; }

void Camera::SetPitch(float angle) { pitch = angle; }

void Camera::SetYaw(float angle) { yaw = angle; }

void Camera::SetX(float x) { position.x = x; }

void Camera::SetY(float y) { position.y = y; }

void Camera::SetZ(float z) { position.z = z; }

void Camera::Move(glm::vec3 displacement) { position += displacement; }

void Camera::Rotate(glm::vec3 axis, float angle) {
	RotatePitch(axis.x * angle);
	RotateYaw(axis.y * angle);
	RotateRoll(axis.z * angle);
}

void Camera::SetRotation(float yaw, float pitch, float roll) {
	Camera::yaw = yaw;
	Camera::pitch = pitch;
	Camera::roll = roll;
}

void Camera::SetPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}

void Camera::Reset() {
	yaw = 0.0f;
	pitch = 0.0f;
	roll = 0.0f;
	position = glm::vec3();
}
