#pragma once

class TrainSkillsTab;

class LocationManager
{
public:
	enum class Location {
		Forest,
		AreaJustOutsideTown,
		Town
	};

	void SetUp(TrainSkillsTab* trainSkillsTab_);
	Location GetLocation();
	void SetLocation(Location location_);
	void SetLocation(int index);

private:
	TrainSkillsTab* trainSkillsTab;
	Location location = Location::Forest;
};

