#pragma once

#include <SFML/Window/Event.hpp>

class Event : public sf::Event
{
public:
	bool Handled = false;
	
};
