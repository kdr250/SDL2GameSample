#pragma once
#include "EntityComponentSystem.h"

class PositionComponent : public Component
{
private:
	int xPosition;
	int yPosition;

public:
	int x() const { return xPosition; }
	int y() const { return yPosition; }

	void Init() override
	{
		xPosition = 0;
		yPosition = 0;
	}

	void Update() override
	{
		xPosition++;
		yPosition++;
	}

	void SetPosition(int x, int y)
	{
		xPosition = x;
		yPosition = y;
	}
};
