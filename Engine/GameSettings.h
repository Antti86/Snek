#pragma once
#include <string>
#include <iostream>


class GameSettings
{
public:
	GameSettings(const std::string& filename);
	int GetnPoison() const;
	int GetnFood() const;
	int GetObstacleSpawnRate() const;
	float GetSnakeSpeedUp() const;
private:
	int nPoison;
	int nFood;
	int ObstacleSpawnRate;
	float SnakeSpeedUp;
};