#pragma once
#include "Agent.h"
class Zombie : public Agent
{
public:
	void init(glm::vec2 _position);
	Zombie();
	~Zombie();

	void update(const std::vector<std::string>& leveldata,
		std::vector<Human*> & humans,
		std::vector<Zombie*>& zombies);
};

