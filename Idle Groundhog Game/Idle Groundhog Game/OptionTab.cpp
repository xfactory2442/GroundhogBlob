#include "OptionTab.h"

OptionTab::OptionTab(sf::RenderWindow* window_, Input* inp, SceneManager* scene,
    SkillsManager* skill, TimeClass* timeClass_, sf::Font* font_, LocationManager* location_)
    : Tabs(window_, inp, scene, skill, timeClass_, font_, location_)
{
	saveButton = new Button(0, "Save", sf::Vector2f(0, 50), sf::Vector2f(100, 50),
		font, 30, sf::Vector2f(2, 5), sf::Color::Black);
	saveButton->setFillColor(sf::Color::White);

	loadButton = new Button(0, "Load", sf::Vector2f(101, 50), sf::Vector2f(100, 50),
		font, 30, sf::Vector2f(2, 5), sf::Color::Black);
	loadButton->setFillColor(sf::Color::White);
}

void OptionTab::SetUpSaveAndLoad(SaveAndLoad* saveAndLoad_)
{
	saveAndLoad = saveAndLoad_;
}

void OptionTab::Update()
{
	if (input->GetMouseLeftDown()) {
		if (saveButton->Collision(window->mapPixelToCoords(input->GetMouse())) > -1) {
			input->SetMouseLeftDown(false);
			saveAndLoad->Save();
		}
		else if (loadButton->Collision(window->mapPixelToCoords(input->GetMouse())) > -1) {
			input->SetMouseLeftDown(false);
			saveAndLoad->Load();
		}
	}
}

void OptionTab::Render()
{
	window->draw(*saveButton);
	saveButton->RenderButtonText(window);
	window->draw(*loadButton);
	loadButton->RenderButtonText(window);
}
