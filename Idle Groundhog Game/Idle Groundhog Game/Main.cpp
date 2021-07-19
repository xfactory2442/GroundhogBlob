#include <SFML/Graphics.hpp>
#include <ctime>
#include <time.h>       /* time */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include "Input.h"
#include "SceneManager.h"
#include "Skills.h"
#include "TimeClass.h"
#include "Unlocks.h"
#include "SkillsManager.h"
#include "LocationManager.h"
#include "SaveAndLoad.h"

#include "BasicTabBackground.h"
#include "TrainSkillsTab.h"
#include "QuestTab.h"
#include "TravelTab.h"
#include "LogTab.h"
#include "ResetInfoTab.h"
#include "OptionTab.h"

int main() {
	//Create the window.
	sf::RenderWindow window(sf::VideoMode(800, 800), "Idle Groundhogs Game");

	srand((int)time(NULL));

	//Initialise Clock Object.
	sf::Clock clock;

	//Initialise Input Object.
	Input input;

	//Initialse SceneManager Object.
	SceneManager sceneManager;

	//Initalise LocationManager Object.
	LocationManager location;

	//Initalise TimeClass Object.
	TimeClass timeClass;

	//Initialise Font Object.
	sf::Font font;
	font.loadFromFile("fonts/consola.ttf");

	//Initialise the experience bar textures.
	sf::Texture bar;
	sf::Texture barOutline;
	bar.loadFromFile("Sprites/barFill.png");
	barOutline.loadFromFile("Sprites/barBorder.png");

	//Set up array of skills.
	SkillsManager skills;
	skills.Init(&font, &window);

	//Add the skills that are originally to be in the vector to the vector.
	skills.AddSkill(0);

	//Set up the tabs.
	BasicTabBackground background(&window, &input, &sceneManager, &skills, &timeClass, &font,
		&location);
	LogTab logTab(&window, &input, &sceneManager, &skills, &timeClass, &font, &location);
	TrainSkillsTab skillTab(&bar, &barOutline, &logTab, 
		&window, &input, &sceneManager, &skills, &timeClass, &font, &location);
	QuestTab questTab(&skillTab, 
		&window, &input, &sceneManager, &skills, &timeClass, &font, &location);
	TravelTab travelTab(&window, &input, &sceneManager, &skills, &timeClass, &font, &location);
	ResetInfoTab resetInfo(&skillTab, 
		&window, &input, &sceneManager, &skills, &timeClass, &font, &location);
	OptionTab options(&window, &input, &sceneManager, &skills, &timeClass, &font, &location);

	//Initalise Unlocks object.
	Unlocks unlocks(&skills, &skillTab, &background, &travelTab, &location);

	timeClass.Init(&logTab, &unlocks, &questTab, &skillTab, &resetInfo, &background, &window, 
		&font, &input, &travelTab);

	questTab.ReadInQuests();
	questTab.AddQuest(0);
	location.SetUp(&skillTab);

	SaveAndLoad saveAndLoad(&skillTab, &questTab, &unlocks, &timeClass, &location);
	options.SetUpSaveAndLoad(&saveAndLoad);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0.f, 0.f,
					(float)event.size.width, (float)event.size.height)));
				window.setSize(sf::Vector2u(800, 800));
				break;
			case sf::Event::KeyPressed:
				// update input class
				input.SetKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				input.SetKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				input.SetMouseXPosition(event.mouseMove.x);
				input.SetMouseYPosition(event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.SetMouseLeftDown(true);
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					//update input class
					input.SetMouseRightDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.SetMouseLeftDown(false);
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					//update input class
					input.SetMouseRightDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}
		}
		float dt = clock.restart().asSeconds();

		background.RenderStart();
		//Complete the actions of the previous day.
		timeClass.Update();
		background.UpdateDay();

		//Depending on scene, check input for that scene and render everything but UI.
		switch (sceneManager.GetScene()) {
		case SceneManager::Scene::Training:
			skillTab.Update(dt);
			skillTab.Render();
			break;
		case SceneManager::Scene::Quests:
			questTab.Update(dt);
			questTab.Render();
			break;
		case SceneManager::Scene::Travel:
			travelTab.Update();
			travelTab.Render();
			break;
		case SceneManager::Scene::ResetInfo:
			resetInfo.Render();
			break;
		case SceneManager::Scene::Log:
			logTab.Update(dt);
			logTab.Render();
			break;
		case SceneManager::Scene::Options:
			options.Update();
			options.Render();
			break;
		}

		//Render the UI;
		timeClass.Render();
		background.RenderUI();
		switch (sceneManager.GetScene()) {
		case SceneManager::Scene::Training:
			skillTab.RenderUI(); 
			break;
		case SceneManager::Scene::Travel:
			travelTab.RenderUI();
			break;
		}
		//End rendering.
		background.RenderEnd();
		
	}
}