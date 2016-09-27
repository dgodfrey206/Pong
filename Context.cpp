#include "stdafx.h"
#include "Context.h"

std::size_t Context::paddleSpeed = 60;
std::size_t Context::ballSpeed = 40;

sf::Vector2f Context::initialBallDirection() {
	float angle = 64.0;

	float x_movement = 0.0;
	float y_movement = 0.0;

	x_movement = ballSpeed * cos(angle);
	y_movement = ballSpeed * sin(angle);
	return{ x_movement, y_movement };
}

Context::Context() : ballMovement(initialBallDirection())
{ }
