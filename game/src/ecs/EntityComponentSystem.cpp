#include "EntityComponentSystem.h"

void Entity::AddGroup(Group mGroup)
{
	groupBitSet[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}
