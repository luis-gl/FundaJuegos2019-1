#include "Zombie.h"



void Zombie::init(glm::vec2 _position)
{
	position = _position;
	color.r = 0;
	color.g = 180;
	color.b = 0;
	color.a = 255;
}

Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}

void Zombie::update(const std::vector<std::string>& leveldata, std::vector<Human*>& humans, std::vector<Zombie*>& zombies)
{
}
