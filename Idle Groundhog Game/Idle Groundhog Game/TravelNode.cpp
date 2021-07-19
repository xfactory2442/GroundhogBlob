#include "TravelNode.h"

TravelNode::TravelNode(string placeName_, map<Skills*, int> requirements_, int time_,
	bool revisitable, LocationManager::Location location_, sf::Vector2f nodePosition,
	sf::Font* font)
{
	//Initialise the node position and colour.
	setPosition(nodePosition);
	setSize(sf::Vector2f(20, 20));
	setFillColor(sf::Color::Red);

	nodeHitbox.left = nodePosition.x;
	nodeHitbox.top = nodePosition.y;
	nodeHitbox.width = 20;
	nodeHitbox.height = 20;

	//Initialise the node's info panel's colour.
	infoPanel.setFillColor(sf::Color::Black);

	//Initalise the info panels text.
	infoText.setFillColor(sf::Color::Red);
	infoText.setFont(*font);
	infoText.setCharacterSize(15);

	placeName = placeName_;
	requirements = requirements_;
	location = location_;
	time = time_;

	FormatText();
}

int TravelNode::Collision(sf::Vector2f mousePosition, Input* input, LocationManager* location_)
{
	if (nodeHitbox.contains(mousePosition)) {
		show = true;
		if (input->GetMouseLeftDown() && CheckRequirements() 
			&& location_->GetLocation() != location
			&& (visited == false || revisitable == true)) {
			input->SetMouseLeftDown(false);
			location_->SetLocation(location);
			visited = true;
			return 2;
		}
		return 1;
	}
	show = false;
	return 0;
}

bool TravelNode::Render(sf::RenderWindow* window)
{
	if (show) {
		window->draw(infoPanel);
		window->draw(infoText);
		return true;
	}
	return false;
}

bool TravelNode::CheckRequirements()
{
	map<Skills*, int>::iterator it = requirements.begin();
	for (pair<Skills*, int> element : requirements) {
		if (element.first->GetLevel() < element.second) {
			return false;
		}
	}

	return true;
}

string TravelNode::GetName()
{
	return placeName;
}

void TravelNode::SetVisited(bool vis)
{
	visited = vis;
}

int TravelNode::GetTime()
{
	return time;
}

void TravelNode::FormatText()
{
	string text = placeName + "\n";
	int numLines = 1;

	map<Skills*, int>::iterator it = requirements.begin();
	for (pair<Skills*, int> element : requirements) {
		text += element.first->GetName() + ": " + to_string(element.second) + "\n";
		numLines++;
	}

	infoText.setString(text);

	infoPanel.setPosition(getPosition().x + 20.0f, getPosition().y - (numLines + 1) * 15.0f + 20.0f);
	infoPanel.setSize(sf::Vector2f(160.0f, ((float)numLines + 1.5f) * 15.0f));
	infoText.setPosition(getPosition().x + 27.5f, getPosition().y - ((float)numLines + 0.5f) * 15.0f + 20.0f);
}
