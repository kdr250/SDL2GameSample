#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID GetComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void Init() {};
	virtual void Update() {};
	virtual void Draw() {};

	virtual ~Component() {};
};

class Entity
{
private:
	bool isActive = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:
	void Update()
	{
		for (auto& component : components) component->Update();
	}

	void Draw()
	{
		for (auto& component : components) component->Draw();
	};

	bool IsActive() const { return isActive; };
	void Destroy() { isActive = false; };

	template <typename T>
	bool HasComponent() const
	{
		return componentBitSet[GetComponentTypeID<T>];
	}

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uniquePtr{ c };
		components.emplace_back(std::move(uniquePtr));

		componentArray[GetComponentTypeID<T>()] = c;
		componentBitSet[GetComponentTypeID<T>()] = true;

		c->Init();
		return *c;
	}

	template<typename T> T& GetComponent() const
	{
		auto ptr(componentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void Update()
	{
		for (auto& entity : entities) entity->Update();
	}

	void Draw()
	{
		for (auto& entity : entities) entity->Draw();
	}

	void Refresh()
	{
		entities.erase(
			std::remove_if(
				std::begin(entities),
				std::end(entities),
				[](const std::unique_ptr<Entity>& mEntity) {
					return !mEntity->IsActive();
				}
			),
			std::end(entities)
		);
	}

	Entity& AddEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uniquePtr{ e };
		entities.emplace_back(std::move(uniquePtr));
		return *e;
	}
};
