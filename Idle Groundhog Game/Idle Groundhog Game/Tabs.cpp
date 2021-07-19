#include "Tabs.h"

//Set up multi tab variables.
Tabs::Tabs(sf::RenderWindow* window_, Input* inp, SceneManager* scene, SkillsManager* skill,
	TimeClass* timeClass_, sf::Font* font_, LocationManager* location_)
{
	window = window_;
	input = inp;
	sceneManager = scene;
	skills = skill;
	timeClass = timeClass_;
	font = font_;
	location = location_;
}
