#pragma once

#include<vector>
#include"Foundation.h"

class Pylon
{
public:
	static enum class Color
	{
		Red,
		Black
	};

private:
	Foundation* m_position;
	std::vector<Bridge*> m_connections;
	std::vector<std::pair<int8_t, int8_t>> m_connectionPoints;
	Color m_color;

public:
	Pylon();
	Pylon(Foundation*, Color);
	Pylon(const Pylon&);
	Pylon& operator=(const Pylon&);
	virtual ~Pylon();
};

