#include "stdafx.h"
#include "Mechanics.h"
#include "Collision.h"

Pong::Pong() : targets(10) {
	ball.setFillColor(sf::Color::Cyan);
	paddle.setFillColor(sf::Color::Red);
	reset();
}

sf::Vector2f Context::paddleSize(20.f, 10.f);

void Pong::run() {
	// Delta-time is the time between two frames.
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	// The game will run at 60 frames per second
	auto TimePerFrame = sf::seconds(1.f / 60.f);
	while (window.isOpen()) {
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Pong::processEvents() {
	for (sf::Event event; window.pollEvent(event); ) {
		if (event.type == sf::Event::Closed ||
			(event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Return))) {
			window.close();
			break;
		}
		// Look for a keypressed event so we an handle input
		if (event.type == sf::Event::KeyPressed) {
			handlePlayerInput(event.key.code, true);
		}
		if (event.type == sf::Event::KeyReleased) {
			handlePlayerInput(event.key.code, false);
		}
	}
}


void Pong::update(sf::Time deltaTime) {
	// direction of the paddle
	sf::Vector2f paddleMovement(0.f, 0.f);
	// Keep the paddle within bounds. If it's outside the screen we prevent movement
	if (paddle.getPosition().x < 0) movingLeft = false;
	if (paddle.getPosition().x + paddle.getSize().x > screenWidth) movingRight = false;
	if (movingLeft)
		paddleMovement.x -= paddleSpeed;
	if (movingRight)
		paddleMovement.x += paddleSpeed;
	if (started) {
		float r = ball.getRadius();
		// Make sure ball is within frame (except the bottom frame where we reset the game)
		if (ball.getPosition().y < 0) ballMovement.y = -ballMovement.y;
		if (ball.getPosition().x < 0 || ball.getPosition().x + 2 * r > screenWidth) ballMovement.x = -ballMovement.x;
		// If the ball touches the bottom then we restart the game
		if (ball.getPosition().y + 2 * r > screenHeight) {
			return reset();
		}
		// check collision between ball and paddle
		switch (paddleCollision(ball, paddle)) {
		case HIT_TYPE::TOPBOTTOMHIT:
			ballMovement.y = -ballMovement.y;
		case HIT_TYPE::LEFTRIGHTHIT:
			ballMovement.x = -ballMovement.x;
		}

		// check collision between ball and targets
		for (auto it = targets.begin(); it != targets.end();) {
			switch (targetCollision(ball, *it)) {
			case HIT_TYPE::TOPBOTTOMHIT:
				ballSpeed += 10;
				// remove target
				it = targets.erase(it);
				// reverse the vertical direction
				ballMovement.y = -ballMovement.y;
				break;
			case HIT_TYPE::LEFTRIGHTHIT:
				ballSpeed += 10;
				// remove target
				it = targets.erase(it);
				// reverse the horizontal direction
				ballMovement.x = -ballMovement.x;
				break;
			default:
				it++;
			}
		}
		ball.move(ballMovement * deltaTime.asSeconds());
	}
	paddle.move(paddleMovement * deltaTime.asSeconds());
}

void Pong::render() {
	// clear current frame with black
	window.clear(sf::Color::Black);
	// draw the shape to the screen
	for (auto& target : targets)
		window.draw(target);
	window.draw(paddle);
	window.draw(ball);
	// display the next frame
	window.display();
}

void Pong::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
	//std::cout << paddle.getPosition().x << " " << paddle.getPosition().y << '\n';

	// Determine if we are moving left or right so that later we can change
	// the (x,y) of the paddle
	if (key == sf::Keyboard::Left) {
		if (!started) started = true;
		setWhere(isPressed, false);
	}
	if (key == sf::Keyboard::Right) {
		if (!started) started = true;
		setWhere(false, isPressed);
	}
}

void Pong::reset() {
	ball.setPosition(screenWidth / 2, screenHeight / 2);
	paddle.setPosition(screenWidth / 2, screenHeight - 20);
	started = movingLeft = movingRight = false;
	ballMovement = initialBallDirection();
	paddleSpeed = 60;
	ballSpeed = 40;

	targets.clear();
	targets.resize(10);

	for (auto& target : targets) {
		target.setSize(sf::Vector2f(15, 10));
		target.setFillColor(sf::Color::Red);
	}

	int i = 0, n = 0;
	for (auto it = targets.begin(); it != targets.end(); ++it, ++i) {
		float x = 10.f * i + n;
		it->setPosition(x, 10);
		n += 10;
	}
}
