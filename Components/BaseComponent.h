#pragma once

#include "Entity.h"

class BaseComponent : public Entity
{
public:
	BaseComponent();
	
	virtual ~BaseComponent();

	void Destroy();

	void Init();

	void BaseUpdate();

	void BaseDraw();

	virtual void Update() = 0;

	virtual void Draw() = 0;


	
};