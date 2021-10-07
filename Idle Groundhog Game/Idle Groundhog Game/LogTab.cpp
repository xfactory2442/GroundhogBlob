#include "LogTab.h"

LogTab::LogTab(sf::RenderWindow* window_, Input* inp, SceneManager* scene, SkillsManager* skill,
    TimeClass* timeClass_, sf::Font* font_, LocationManager* location_)
    : Tabs(window_, inp, scene, skill, timeClass_, font_, location_)
{
}

bool LogTab::Update(float dt)
{
    return false;
}

void LogTab::Render()
{
    for (int i = 0; i < log.size(); i++) {
        window->draw(log[i]);
    }
}

//Moves all the current log items down and addes a new text object to the log.
void LogTab::AddToLog(string text)
{ 
    //Find out the number of lines needed.
    int lines = (int)ceil((float)text.size() / (float)maxLineSize);

    //Format the lines.
    GeneralFunctions::FormatLine(text, maxLineSize, lines);
    
    //Shove the current log parts down by an amount based on the size of the new log.
    for (int i = 0; i < log.size(); i++) {
        log[i].setPosition(log[i].getPosition() + sf::Vector2f(0, 20.0f * (float)lines));
    }
    //If a log goes off the screen, delete it.
    if (log.size() > 0 && log.front().getPosition().y + 20.0f > window->getSize().y) {
        log.erase(log.begin());
    }

    log.push_back(sf::Text());
    log.back().setCharacterSize(15);
    log.back().setPosition(10.0f, 55.0f);
    log.back().setString(text);
    log.back().setFont(*font);
    log.back().setFillColor(sf::Color::White);
}