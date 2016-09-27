#include "Context.h"
#include <list>

class Pong : private Context {
public:
	void run();
	void reset();
	Pong();
private:
	Pong(Pong const&) = delete;
	Pong(Pong&&) = delete;
	Pong& operator=(Pong const&) = delete;
	Pong& operator=(Pong&&) = delete;
private:
	void render();
	void processEvents();
	void update(sf::Time deltaTime);
	void handlePlayerInput(sf::Keyboard::Key, bool isPressed);
	void setWhere(bool left, bool right) {
		movingLeft = left;
		movingRight = right;
	}

	sf::RectangleShape paddle{ paddleSize };
	sf::CircleShape ball{ ballRadius };
	std::list<sf::RectangleShape> targets;
	bool started = false, movingLeft = false, movingRight = false;
};
