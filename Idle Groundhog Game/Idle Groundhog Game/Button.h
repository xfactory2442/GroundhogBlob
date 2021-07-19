#pragma once
#include <SFML/Graphics.hpp>
class Button : public sf::RectangleShape
{
public:
	Button(int type_, std::string nameText_, sf::Vector2f position, sf::Vector2f size,
		sf::Font* font, float fontSize = 15, sf::Vector2f textPosition = sf::Vector2f(2, 5),
		sf::Color color = sf::Color::White, sf::Color textColor = sf::Color::Black);
	int Collision(sf::Vector2f mousePosition);
	void RenderButtonText(sf::RenderWindow* window);

	void SetPosition(sf::Vector2f position_);

	std::string GetButtonName();
private:
	int type = 0;
	sf::Text nameText;
	sf::FloatRect hitbox;
};

