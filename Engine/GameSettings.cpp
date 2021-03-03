#include "GameSettings.h"
#include <fstream>

GameSettings::GameSettings(const std::string& filename)
{
	std::fstream in(filename);

	for (std::string line; std::getline(in, line);)
	{
		if (line == "[Number of Poisons]")
		{
			in >> nPoison;
		}
		else if (line == "[Number of Food]")
		{
			in >> nFood;
		}
		else if (line == "[ObstacleSpawnRate]")
		{
			in >> ObstacleSpawnRate;
		}
		else if (line == "[SnakeSpeedUp]")
		{
			in >> SnakeSpeedUp;
		}
	}
}

int GameSettings::GetnPoison() const
{
	return nPoison;
}

int GameSettings::GetnFood() const
{
	return nFood;
}

int GameSettings::GetObstacleSpawnRate() const
{
	return ObstacleSpawnRate;
}

float GameSettings::GetSnakeSpeedUp() const
{
	return SnakeSpeedUp;
}
