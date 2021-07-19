#include "TravelTab.h"

TravelTab::TravelTab(sf::RenderWindow* window_, Input* inp, SceneManager* scene,
	SkillsManager* skill, TimeClass* timeClass_, sf::Font* font_, LocationManager* location_)
	: Tabs(window_, inp, scene, skill, timeClass_, font_, location_)
{
	infoWindow = new InfoWindow(window, font);

	InitaliseTravelNodes();

	AddTravelNode("Forest");
}

void TravelTab::Update()
{
	if (infoWindow->isAlive()) {
		if (input->GetMouseLeftDown() &&
			infoWindow->Collsion(window->mapPixelToCoords(input->GetMouse()))) {
			input->SetMouseLeftDown(false);
		}
		return;
	}

	//Is the mouse hovering over a travel node?
	for (int i = 0; i < travelNodes.size(); i++) {
		int num = travelNodes[i]->Collision(window->mapPixelToCoords(input->GetMouse()), input, location);
		if (num == 2) {
			infoWindow->ShowWindow("You have travelled to " + travelNodes[i]->GetName());
			timeClass->AdvanceDayByTravel(travelNodes[i]->GetTime());
			return;
		}
		else if (num == 1) {
			return;
		}
	}
}

void TravelTab::Render()
{
	//Render the travel nodes.
	for (int i = 0; i < travelNodes.size(); i++) {
		window->draw(*travelNode[i]);
	}
}

void TravelTab::RenderUI()
{
	//Render the info panel if it is visiable.
	for (int i = 0; i < travelNodes.size(); i++) {
		if (travelNodes[i]->Render(window)) {
			break;
		}
	}

	if (infoWindow->isAlive()) {
		window->draw(*infoWindow);
		infoWindow->Render(window);
	}
}

//Add a travel node to the vector of active travel nodes.
void TravelTab::AddTravelNode(int index)
{
	for (int i = 0; i < travelNodes.size(); i++) {
		if (travelNodes[i]->GetName() == travelNode[index]->GetName()) {
			return;
		}
	}
	travelNodes.push_back(travelNode[index]);
}

void TravelTab::AddTravelNode(string s)
{
	for (int i = 0; i < numTravelNodes; i++) {
		if (travelNode[i]->GetName() == s) {
			AddTravelNode(i);
			break;
		}
	}
}

void TravelTab::Reset()
{
	for (int i = 1; i < numTravelNodes; i++) {
		travelNode[i]->SetVisited(false);
	}
	infoWindow->SetAlive(false);
}

void TravelTab::InitaliseTravelNodes()
{
	sf::Vector2f position;
	map<Skills*, int> requirements;

	//Initalise the node.
	travelNode[0] = new TravelNode("Forest", requirements, 0, false,
		LocationManager::Location::Forest, sf::Vector2f(30.0f, (float)window->getSize().y - 60.0f), font);
	travelNode[0]->SetVisited(true);
	requirements.clear();


	requirements.insert(std::pair<Skills*, int>(skills->GetSkill(0), 50));
	requirements.insert(std::pair<Skills*, int>(skills->GetSkill(1), 15));
	requirements.insert(std::pair<Skills*, int>(skills->GetSkill(2), 3));
	travelNode[1] = new TravelNode("Area Just Outside Town", requirements, 1, false, 
		LocationManager::Location::AreaJustOutsideTown, sf::Vector2f(100.0f, 
		(float)window->getSize().y - 130.0f), font);
	requirements.clear();
}
