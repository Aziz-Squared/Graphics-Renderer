#include "Camera.h"

void FlyCamera::update(const Input &in, const Time &t)
{
	glm::vec3 moveDir = glm::vec3(0, 0, 0);
	glm::vec3 right = glm::cross(direction, glm::vec3(0, 1, 0));
	glm::vec3 up = glm::cross(right, direction);

	// Direction represents our forward direction
	yaw += in.getMouseAxisHorizontal() * t.getDeltaTime() * 500;
	pitch += in.getMouseAxisVertical() * t.getDeltaTime() * 500;


	pitch = glm::clamp(pitch, -glm::pi<float>() / 2, glm::pi<float>() / 2);

	direction.x = cos(yaw) * sin(pitch);
	direction.y = cos(yaw);
	direction.z = sin(yaw) * sin(pitch);

	glm::mat4 tbn = glm::eulerAngleXYZ(yaw, pitch, roll);

	right = glm::vec3(tbn[0]);
	up = glm::vec3(tbn[1]);
	direction = glm::vec3(tbn[2]);
	


	if (in.getKeyState('W') == Input::DOWN) moveDir += direction;
	if (in.getKeyState('S') == Input::DOWN) moveDir -= direction;
	if (in.getKeyState('A') == Input::DOWN) moveDir -= right;
	if (in.getKeyState('D') == Input::DOWN) moveDir += right;
	if (in.getKeyState('E') == Input::DOWN) moveDir -= up;
	if (in.getKeyState('Q') == Input::DOWN) moveDir += up;


	if (glm::length(moveDir) >= .7f)
	{
		moveDir = glm::normalize(moveDir);
		position += moveDir * t.getDeltaTime() * speed;
	}

}
