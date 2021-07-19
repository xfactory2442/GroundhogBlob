#pragma once
#include <SFML/Graphics.hpp>
#include "LocationManager.h"
#include "Skills.h"
#include "Input.h"
#include "TimeClass.h"

using namespace std;

class TravelNode : public sf::RectangleShape
{
public:
	TravelNode(string placeName_, map<Skills*, int> requirements_, int time_, bool revisitable, 
		LocationManager::Location location_, sf::Vector2f nodePosition, sf::Font* font);
	int Collision(sf::Vector2f mousePosition, Input* input, LocationManager* location_);
	bool Render(sf::RenderWindow* window);

	bool CheckRequirements();

	string GetName();
	void SetVisited(bool vis);
	int GetTime();

private:
	void FormatText();

	//Has the node been visited?
	bool visited = false;
	//Is the node able to be revisited after leaving it.
	bool revisitable;

	//The name of the place.
	string placeName;
	//The requirements for moving to that node.
	map<Skills*, int> requirements;
	//For changing the location when travelling to the node.
	LocationManager::Location location;
	//How long does it take to get there?
	int time;

	//The hitbox of the node.
	sf::FloatRect nodeHitbox;

	//Is the info panel visible?
	bool show = false;
	//The image of the info panel.
	sf::RectangleShape infoPanel;
	//The text of the info panel.
	sf::Text infoText;
};

