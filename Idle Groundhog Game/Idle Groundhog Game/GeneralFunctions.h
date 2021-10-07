#pragma once
#include <string>

using namespace std;

class GeneralFunctions
{
public:
	static string FormatNumber(float num);
	static string FormatNumber(int num);
	static string FormatLine(string s, int maxLineSize);
	static string FormatLine(string s, int maxLineSize, int lines);
	static string FormatReadInText(string s);
	static uint32_t NumTimesDivisibleBy(float number, float denominator);
};

