#include <cctype>
#include <SFML/Graphics.hpp>

struct Context {
	static sf::Vector2f initialBallDirection();

	Context();

	static const unsigned int screenWidth = 200;
	static const unsigned int screenHeight = 200;
	static constexpr float ballRadius = 3;
	static std::size_t paddleSpeed;
	static std::size_t ballSpeed;
	static sf::Vector2f paddleSize;
	sf::Vector2f ballMovement;
protected:
	sf::RenderWindow window{ sf::VideoMode{ screenWidth, screenHeight }, "Pong Pong!" };
};
