#pragma once
#include "Tabs.h"
#include "Unlocks.h"
#include "TravelNode.h"
#include "InfoWindow.h"

class TravelTab : public Tabs
{
public:

	TravelTab(sf::RenderWindow* window_, Input* inp, SceneManager* scene, SkillsManager* skill,
		TimeClass* timeClass_, sf::Font* font_, LocationManager* location_);
	void Update();
	void Render();
	void RenderUI();

	void AddTravelNode(int index);
	void AddTravelNode(string s);

	void Reset();
	
private:
	void InitaliseTravelNodes();

	static const int numTravelNodes = 2;
	TravelNode* travelNode[numTravelNodes];
	vector<TravelNode*> travelNodes;

	int maxLineSize = 40;

	InfoWindow* infoWindow;
};

