#pragma once
#define GLM_SWIZZLE
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

#include "Input.h"
#include "Timer.h"

class FlyCamera
{
public:
	glm::vec3 position, direction;
	glm::mat4 transform;

	// YAW is along the X
	// PITCH is along the X
	// ROLL is along the Z
	float yaw, pitch, roll;

	// Make sure near is greater than 0
	float aspect, fov, near, far;
	
	float speed;

public:
	FlyCamera(float a_aspect = 16.f/9.f, float a_fov = 45.f, float a_near = 1.f, float a_far = 5.f)
		:aspect(a_aspect), fov(a_fov), near(a_near), far(a_far), 
			direction(0,0,1), speed(20), pitch(0), yaw(0), roll(0)
	{}

	void update(const class Input &, const class Time &);

	void jumpTo(glm::vec3 jump)
	{
		position = jump;
	}

	void lookAt(const glm::vec3 &target)
	{
		direction = glm::normalize(target - position);
	}

	glm::mat4	getView() const
	{
		return glm::inverse(transform);
	}
	glm::mat4	getProjection() const
	{
		return glm::perspective(fov, aspect, near, far);
	}

};