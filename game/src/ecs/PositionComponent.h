#pragma once

#include "Components.h"

class PositionComponent : public Component
{
private:
	int xPosition;
	int yPosition;

public:
	PositionComponent()
	{
		xPosition = 0;
		yPosition = 0;
	}

	PositionComponent(int x, int y)
	{
		xPosition = x;
		yPosition = y;
	}

	int x() const { return xPosition; }
	int y() const { return yPosition; }

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

