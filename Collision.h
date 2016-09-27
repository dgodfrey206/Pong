#pragma once

#include "stdafx.h"
#include <SFML/Graphics.hpp>
enum class HIT_TYPE {
	LEFTRIGHTHIT,
	TOPBOTTOMHIT,
	INVALID = -1
};


HIT_TYPE paddleCollision(sf::CircleShape const& ball, sf::RectangleShape const& paddle) {
	sf::Vector2f ballPosition = ball.getPosition();
	sf::Vector2f paddlePosition = paddle.getPosition();
	float ballRadius = ball.getRadius(), paddleWidth = paddle.getSize().x;

	// check if ball's position is within ({k | p.x <= k <= p.x + width}, p.y)
	// this is the top of the paddle object
	bool topHit = (paddlePosition.x <= ballPosition.x
		&& (ballPosition.x + ballRadius) <= paddlePosition.x + paddleWidth)
		&& static_cast<int>(ballPosition.y + ballRadius) == static_cast<int>(paddlePosition.y);

	bool leftHit = ((int)ball.getPosition().x == int(paddle.getPosition().x + paddle.getSize().x)) && ((int)paddle.getPosition().y <= (int)ball.getPosition().y &&
		(int)ball.getPosition().y <= int(paddle.getPosition().y + paddle.getSize().y));
	bool rightHit = (int(ball.getPosition().x + ball.getRadius()) == (int)paddle.getPosition().x && ((int)paddle.getPosition().y <= (int)ball.getPosition().y) && ((int)ball.getPosition().y <= int(paddle.getPosition().y + paddle.getSize().y)));

	if (topHit)				 return HIT_TYPE::TOPBOTTOMHIT;
	if (leftHit || rightHit) return HIT_TYPE::LEFTRIGHTHIT;
	return HIT_TYPE::INVALID;
}

HIT_TYPE targetCollision(sf::CircleShape const& ball, sf::RectangleShape const& target) {
	sf::Vector2f ballPosition = ball.getPosition();
	sf::Vector2f targetPosition = target.getPosition();
	float ballRadius = ball.getRadius(), targetWidth = target.getSize().x, targetHeight = target.getSize().y;
	// check if ball's position is within ({k | t.x <= k <= t.x + width}, t.y)
	bool topHit = (targetPosition.x <= (ballPosition.x /*- ballRadius*/)
		&& (ballPosition.x + ballRadius) <= targetPosition.x + targetWidth)
		&& static_cast<int>(ballPosition.y + /*2 */ ballRadius) == static_cast<int>(targetPosition.y);

	bool bottomHit = (targetPosition.x <= (ballPosition.x - ballRadius)
		&& (ballPosition.x + ballRadius) <= targetPosition.x + targetWidth)
		&& static_cast<int>(ballPosition.y) == static_cast<int>(targetPosition.y + targetHeight);

	bool leftHit = ((int)ball.getPosition().x == int(target.getPosition().x + target.getSize().x)) && ((int)target.getPosition().y <= (int)ball.getPosition().y &&
		(int)ball.getPosition().y <= int(target.getPosition().y + target.getSize().y));
	bool rightHit = (int(ball.getPosition().x + ball.getRadius()) == (int)target.getPosition().x && ((int)target.getPosition().y <= (int)ball.getPosition().y) && ((int)ball.getPosition().y <= int(target.getPosition().y + target.getSize().y)));

	if (topHit || bottomHit) return HIT_TYPE::TOPBOTTOMHIT;
	if (leftHit || rightHit) return HIT_TYPE::LEFTRIGHTHIT;
	return HIT_TYPE::INVALID;
}
