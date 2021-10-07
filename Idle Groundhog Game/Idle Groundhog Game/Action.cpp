#include "Action.h"
#include <iostream>

Action::Action(vector<LocationManager::Location> locationsWhereAvailable_, string name_, 
	string logString_, vector<Skills*> actionsSkills,  sf::Vector2f position,
	sf::Texture* barTexture, sf::Texture* barOutlineTexture, sf::Font* font, float barSize_,
	float fillMax_, float fillAmount_, string unlockText_)
{
	name = name_;
	skills = actionsSkills;
	barSize = barSize_;
	fillAdd = fillAmount_;
	initFillMax = fillMax_;
	fillMax = initFillMax;
	logString = logString_;
	unlockText = unlockText_;
	locationsWhereAvailable = locationsWhereAvailable_;

	for (int i = 0; i < skills.size(); i++) {
		std::cout << "Action " << name << ": " << std::endl;
		std::cout << skills[i]->GetName() << "\n\n";
	}

	//Initalise the action bar's name.
	barName.setCharacterSize(20);
	barName.setFillColor(sf::Color::White);
	barName.setString(name_);
	barName.setFont(*font);
	nameHitbox.width = 150.0f;
	nameHitbox.height = 40;

	//Initialise the action bar.
	bar.setSize(sf::Vector2f(0, 40));
	bar.setTexture(barTexture);
	barHitbox.width = barSize;
	barHitbox.height = bar.getSize().y;

	barOutline.setSize(sf::Vector2f(barSize, bar.getSize().y));
	barOutline.setTexture(barOutlineTexture);

	//Set up talent box.
	talentText.setFont(*font);
	talentText.setString("Talent: " + GeneralFunctions::FormatNumber(talent));
	talentText.setFillColor(sf::Color::Red);
	talentText.setCharacterSize(15);

	talentBox.setFillColor(sf::Color::Black);
	talentBox.setSize(sf::Vector2f(155.0f, 30.0f));

	//Set up action box.
	fillText.setFont(*font);
	fillText.setString(GeneralFunctions::FormatNumber(fill) + "/"
		+ GeneralFunctions::FormatNumber(fillMax));
	fillText.setFillColor(sf::Color::Red);
	fillText.setCharacterSize(15);
	fillBox.setSize(sf::Vector2f(175.0f, 30.0f));
	fillBox.setFillColor(sf::Color::Black);
	

	//Initialise Buttons.
	buttons[0] = new Button(0, "M", bar.getPosition() + sf::Vector2f(barSize + 5, 0), 
		sf::Vector2f(15, 40), font, 15, sf::Vector2f(2, 5), sf::Color::Red, sf::Color::Black);
	buttons[1] = new Button(0, "A", bar.getPosition() + sf::Vector2f(barSize + 23, 0), 
		sf::Vector2f(15, 40), font, 15, sf::Vector2f(2, 5), sf::Color::Red, sf::Color::Black);
	buttons[2] = new Button(0, "E", bar.getPosition() + sf::Vector2f(barSize + 41, 0), 
		sf::Vector2f(15, 40), font, 15, sf::Vector2f(2, 5), sf::Color::Red, sf::Color::Black);
}

void Action::DoAction()
{
	//Calculate how much the bar goes up.
	fill += (fillAdd * talent);

	while (fill >= fillMax){
		if (fill >= fillMax) {
			fill -= fillMax;
			if (timesFilledInDay < maxTimesFilledInOneDay) {
				timesFilled++;
				timesFilledInDay++;
				for (int i = 0; i < skills.size(); i++) {
					skills[i]->AddLevels(1);
				}
				fillMax *= fillDifficultyIncrease;
				if (timesFilled % difficultyIncreaseLevel == 0) {
					fillDifficultyIncrease += difficultyIncreaseMultiplier;
				}
			}
		}
	}

	FormatFillBar();
}

string Action::GetLogString()
{
	return logString;
}

string Action::GetUnlockText()
{
	return unlockText;
}

vector<Skills*> Action::GetSkills()
{
	return skills;
}

int Action::GetTimesCompleted()
{
	return timesFilled;
}

string Action::GetName()
{
	return name;
}

float Action::GetFill()
{
	return fill;
}

float Action::GetFillMax()
{
	return fillMax;
}

float Action::GetDifficultyIncrease()
{
	return fillDifficultyIncrease;
}

float Action::GetTalent()
{
	return talent;
}

int Action::GetTimesFilled()
{
	return timesFilled;
}

void Action::SetFill(float fill_)
{
	fill = fill_;
}

void Action::SetMaxFill(float maxFill_)
{
	fillMax = maxFill_;
}

void Action::SetDifficultyIncrease(float difficultyIncrease_)
{
	fillDifficultyIncrease = difficultyIncrease_;
}

void Action::SetTalent(float talent_)
{
	talent = talent_;
}

void Action::SetTimesFilled(int timesFilled_)
{
	timesFilled = timesFilled_;
}

int Action::CollideWithButtons(sf::Vector2f mousePosition)
{
	//Collide with buttons for each of the time blocks.
	for (int i = 0; i < 3; i++) {
		if (buttons[i]->Collision(mousePosition) > -1) {
			return i;
		}
	}
	return -1;
}

void Action::CollideWithAction(sf::Vector2f mousePosition)
{
	showTalent = nameHitbox.contains(mousePosition);
	showFillAmount = barHitbox.contains(mousePosition);
}

void Action::FormatFillBar()
{
	//Set the fill text.
	fillText.setString(GeneralFunctions::FormatNumber(fill) + "/"
		+ GeneralFunctions::FormatNumber(fillMax));

	//Set the size of the bar.
	bar.setSize(sf::Vector2f((fill / fillMax) * barSize, bar.getSize().y));

	talentText.setString("Talent: " + GeneralFunctions::FormatNumber(talent));

	fillText.setString(GeneralFunctions::FormatNumber(fill) + "/"
		+ GeneralFunctions::FormatNumber(fillMax));
}

void Action::SetButtonColourRed(int i)
{
	buttons[i]->setFillColor(sf::Color::Red);
}

void Action::SetButtonColourGreen(int i)
{
	buttons[i]->setFillColor(sf::Color::Green);
}

void Action::RenderAction(sf::RenderWindow* window)
{
	//Render the action bar's name and the action bar.
	window->draw(barName);
	window->draw(bar);
	window->draw(barOutline);
	//Render the time buttons.
	for (int i = 0; i < 3; i++) {
		window->draw(*buttons[i]);
		buttons[i]->RenderButtonText(window);
	}
}

void Action::RenderUI(sf::RenderWindow* window)
{
	if (showTalent) {
		window->draw(talentBox);
		window->draw(talentText);
	}
	else if (showFillAmount) {
		window->draw(fillBox);
		window->draw(fillText);
	}
}

vector<LocationManager::Location> Action::GetLocationsWhereAvailable()
{
	return locationsWhereAvailable;
}

void Action::SetUnlocked(bool unlocked_)
{
	unlocked = unlocked_;
}

bool Action::GetUnlocked()
{
	return unlocked;
}

void Action::SetPosition(sf::Vector2f position)
{
	barName.setPosition(position.x, position.y + 5);
	nameHitbox.left = position.x;
	nameHitbox.top = position.y;
	bar.setPosition(position.x + 160, position.y);
	barHitbox.left = bar.getPosition().x;
	barHitbox.top = bar.getPosition().y;
	barOutline.setPosition(bar.getPosition());
	talentText.setPosition(position.x + 80, position.y + 15);
	talentBox.setPosition(position.x + 70, position.y + 5);
	fillText.setPosition(bar.getPosition() + sf::Vector2f(barSize + 15, 15));
	fillBox.setPosition(bar.getPosition() + sf::Vector2f(barSize + 5, 5));
	for (int i = 0; i < 3; i++) {
		buttons[i]->SetPosition(bar.getPosition() + sf::Vector2f(barSize + 5.0f + 18.0f * i, 0));
	}
}

void Action::ResetActionDay()
{
	timesFilledInDay = 0;
}

float Action::CalculateTalent()
{
	return ((float)timesFilled / 10.0f);
}

void Action::Reset()
{
	talent += CalculateTalent();
	timesFilled = 0;
	fill = 0;
	fillMax = initFillMax;
	fillDifficultyIncrease = initFillDifficultyIncrease;
	unlocked = false;

	talentText.setString("Talent: " + GeneralFunctions::FormatNumber(talent));
	bar.setSize(sf::Vector2f((fill / fillMax) * barSize, bar.getSize().y));
	fillText.setString(GeneralFunctions::FormatNumber(fill) + "/"
		+ GeneralFunctions::FormatNumber(fillMax));
}
