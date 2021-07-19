#include "LocationManager.h"
#include "TrainSkillsTab.h"

void LocationManager::SetUp(TrainSkillsTab* trainSkillsTab_)
{
	trainSkillsTab = trainSkillsTab_;
}

LocationManager::Location LocationManager::GetLocation()
{
	return location;
}

void LocationManager::SetLocation(Location location_)
{
	location = location_;
	trainSkillsTab->ChangeLocation();
}

void LocationManager::SetLocation(int index)
{
	location = (Location)index;
}
