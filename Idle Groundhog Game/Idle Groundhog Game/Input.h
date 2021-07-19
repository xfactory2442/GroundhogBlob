#pragma once
#include <SFML/Graphics.hpp>
class Input
{
private:
	// Structure to represent Mouse
	struct Mouse
	{
		int x = 0;
		int y = 0;
		bool left = false;
		bool right = false;
	};

public:

	void SetKeyDown(int key);
	void SetKeyUp(int key);
	void SetMouseXPosition(int x);
	void SetMouseYPosition(int y);
	void SetMouseLeftDown(bool down);
	void SetMouseRightDown(bool down);
	sf::Vector2i GetMouse();
	bool GetMouseLeftDown();
	bool GetKeyDown(int key);

private:
	const double timeForDrag = 0.2;
	double timeOfClickLeft = 0;
	double timeOfClickRight = 0;

	bool keys[256]{ false };
	Mouse mouse;
};

