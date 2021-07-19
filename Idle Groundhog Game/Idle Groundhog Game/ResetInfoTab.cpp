#include "ResetInfoTab.h"
#include "TrainSkillsTab.h"

ResetInfoTab::ResetInfoTab(TrainSkillsTab* trainSkillsTab_, sf::RenderWindow* window_, 
	Input* inp, SceneManager* scene, SkillsManager* skill, TimeClass* timeClass_, 
	sf::Font* font_, LocationManager* location_)
	: Tabs(window_, inp, scene, skill, timeClass_, font_, location_)
{
	trainSkillsTab = trainSkillsTab_;
}

void ResetInfoTab::Render()
{
	//Render the reset windows.
	for (int i = 0; i < resetInfo.size(); i++) {
		window->draw(resetInfo[i].background);
		for (int j = 0; j < resetInfo[i].changesText.size(); j++) {
			window->draw(resetInfo[i].changesText[j]);
		}
	}
}

void ResetInfoTab::AddAResetWindow(int resetNum)
{
	resetInfo.push_back(ResetInfo());

	//Adds a text at the top of the reset window which says what reset the data is about.
	resetInfo.back().changesText.push_back(sf::Text());
	resetInfo.back().changesText.back().setCharacterSize(20);
	resetInfo.back().changesText.back().setString("Reset" + to_string(resetNum) + ":");
	resetInfo.back().changesText.back().setFont(*font);
	resetInfo.back().changesText.back().setPosition(5.0f, 55.0f);
	resetInfo.back().changesText.back().setFillColor(sf::Color::Red);

	//Get the reset data from the skills tab.
	vector<string> s = trainSkillsTab->GetResetData();

	//For the number of actions with reset data, create a text object and display
	//the reset data.
	int totalLines = 0;
	for (int i = 0; i < s.size(); i++) {
		int lines = (int)ceilf((float)s[i].size() / (float)maxLineSize);
		s[i] = GeneralFunctions::FormatLine(s[i], maxLineSize, lines);
		
		resetInfo.back().changesText.push_back(sf::Text());
		resetInfo.back().changesText.back().setCharacterSize(20);
		resetInfo.back().changesText.back().setString(s[i]);
		resetInfo.back().changesText.back().setFont(*font);
		resetInfo.back().changesText.back().setPosition(25.0f, 80.0f + totalLines * 25.0f);
		resetInfo.back().changesText.back().setFillColor(sf::Color::Red);

		totalLines += lines;
	}
	totalLines++;

	//Create the reset window background.
	resetInfo.back().background.setFillColor(sf::Color::White);
	resetInfo.back().background.setPosition(0.0f, 50.0f);
	float backgroundSize = (float)totalLines * 25.0f + 10.0f;
	resetInfo.back().background.setSize(sf::Vector2f(window->getSize().x - 120.0f, backgroundSize));

	//Push odwn all of the previous reset windows to make room for the new one at the top of the list.
	PushDownResetWindows(backgroundSize);
}

//Pushes down all of the previous reset windows so make room for the new one at the top of the list.
void ResetInfoTab::PushDownResetWindows(float backgroundSize)
{
	backgroundSize += 2;
	for (int i = 0; i < resetInfo.size() - 1; i++) {
		for (int j = 0; j < resetInfo[i].changesText.size(); j++) {
			resetInfo[i].changesText[j].setPosition(
				resetInfo[i].changesText[j].getPosition() + sf::Vector2f(0.0f, backgroundSize)
			);
		}
		resetInfo[i].background.setPosition(
			resetInfo[i].background.getPosition() + sf::Vector2f(0.0f, backgroundSize)
		);
	}
}
