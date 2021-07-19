#include "BasicTabBackground.h"

BasicTabBackground::BasicTabBackground(sf::RenderWindow* window_, Input* inp, 
	SceneManager* scene, SkillsManager* skill, TimeClass* timeClass_, 
	sf::Font* font_, LocationManager* location_)
	: Tabs(window_, inp, scene, skill, timeClass_, font_, location_)
{
	skillsSection.setSize(sf::Vector2f(120.0f, (float)window->getSize().y - 100.0f));
	skillsSection.setPosition((float)window->getSize().x - skillsSection.getSize().x, 50.0f);
	skillsSection.setFillColor(sf::Color(50, 50, 50, 255));

	//Initialise the background for the tabs.
	tabBackground.setPosition(0.0f, 50.0f);
	tabBackground.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y - 50.0f));
	tabBackground.setFillColor(sf::Color(100, 100, 100, 255));

	//Initialise NextDayButton.
	nextDayButton = new Button(0, "Next Day", sf::Vector2f(600.0f, 0.0f), 
		sf::Vector2f(200.0f, 50.0f), font, 30.0f, sf::Vector2f(2.0f, 5.0f), sf::Color::Black);
	nextDayButton->setFillColor(sf::Color::White);

	dayText.setCharacterSize(30);
	dayText.setFillColor(sf::Color::White);
	dayText.setPosition(450, 5);
	dayText.setFont(*font);
	SetDayText();

	lifeSpanText.setCharacterSize(20);
	lifeSpanText.setFillColor(sf::Color::White);
	lifeSpanText.setPosition(10, 5);
	lifeSpanText.setFont(*font);
	lifeSpanText.setString("Life Span: " + GeneralFunctions::FormatNumber(timeClass->GetLifeSpan()));

	//Initalise scene change buttons.
	sceneButtons[0] = new Button(0, "Skills", sf::Vector2f(0, 30), sf::Vector2f(55, 20), font);
	sceneButtons[1] = new Button(1, "Quests", sf::Vector2f(56, 30), sf::Vector2f(55, 20), font);
	sceneButtons[2] = new Button(2, "Travel", sf::Vector2f(112, 30), sf::Vector2f(55, 20), font);
	sceneButtons[3] = new Button(3, "Log", sf::Vector2f(168, 30), sf::Vector2f(40, 20), font);
	sceneButtons[4] = new Button(4, "Reset Info", sf::Vector2f(209, 30), sf::Vector2f(85, 20), font);
	sceneButtons[5] = new Button(5, "Options", sf::Vector2f(295, 30), sf::Vector2f(60, 20), font);

	UnlockTab("Skills");
	UnlockTab("Log");
	UnlockTab("Options");
}

void BasicTabBackground::UpdateDay()
{
	if (input->GetMouseLeftDown()) {
		if (nextDayButton->Collision(window->mapPixelToCoords(input->GetMouse())) > -1) {
			input->SetMouseLeftDown(false);
			timeClass->AdvanceDay();
			SetDayText();
		}

		for (int i = 0; i < unlockedTabButtons.size(); i++) {
			int sceneNumber = unlockedTabButtons[i]->Collision(window->mapPixelToCoords(input->GetMouse()));
			if (sceneNumber >= 0) {
				input->SetMouseLeftDown(false);
				sceneManager->ChangeScene(sceneNumber);
			}
		}
	}
}

void BasicTabBackground::RenderStart()
{
	window->clear(sf::Color::Black);
	window->draw(tabBackground);
}

void BasicTabBackground::RenderUI()
{
	//Draws the skills section on the right of the window.
	window->draw(skillsSection);
	for (int i = 0; i < skills->GetOpenSkills().size(); i++) {
		skills->GetOpenSkills()[i]->RenderSkill(window);
	}

	window->draw(*nextDayButton);
	nextDayButton->RenderButtonText(window);
	window->draw(dayText);
	window->draw(lifeSpanText);

	for (int i = 0; i < unlockedTabButtons.size(); i++) {
		window->draw(*unlockedTabButtons[i]);
		unlockedTabButtons[i]->RenderButtonText(window);
	}
}

void BasicTabBackground::RenderEnd()
{
	window->display();
}

void BasicTabBackground::SetLifespanText()
{
	lifeSpanText.setString("Life Span: " + GeneralFunctions::FormatNumber(timeClass->GetLifeSpan()));
}

void BasicTabBackground::UnlockTab(int index)
{
	for (int i = 0; i < unlockedTabButtons.size(); i++) {
		if (unlockedTabButtons[i] == sceneButtons[index]) {
			return;
		}
	}
	unlockedTabButtons.push_back(sceneButtons[index]);
}

void BasicTabBackground::UnlockTab(string s)
{
	for (int i = 0; i < numSceneButtons; i++) {
		if (sceneButtons[i]->GetButtonName() == s) {
			UnlockTab(i);
			break;
		}
	}
}

void BasicTabBackground::SetDayText()
{
	dayText.setString("Day: " + to_string(timeClass->GetDay()));
}
