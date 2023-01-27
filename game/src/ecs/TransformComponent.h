#pragma once

#include "Components.h"

class TransformComponent : public Component
{
private:
	int xPosition;
	int yPosition;

public:
	TransformComponent()
	{
		xPosition = 0;
		yPosition = 0;
	}

	TransformComponent(int x, int y)
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

