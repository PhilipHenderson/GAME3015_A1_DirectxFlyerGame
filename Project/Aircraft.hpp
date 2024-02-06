#pragma once
#include "Entity.hpp"
#include <string>

class Aircraft :
    public Entity
{
public:
	enum Type
	{
		Eagle,
		Raptor,
	};


public:
	Aircraft(Type type, Game* game);

	XMFLOAT3 getPosition() const { return mPosition; }
	XMFLOAT3 getForwardVector() const;
	float getPitch() const 
	{
		XMFLOAT3 rotation = getWorldRotation(); // Assuming this function exists and returns the world rotation
		return rotation.x; // Return the Pitch component
	}
	float getYaw() const 
	{
		XMFLOAT3 rotation = getWorldRotation(); // Assuming this function exists and returns the world rotation
		return rotation.y; // Return the Yaw component
	}

	float mRoll;
	void adjustRoll(float amount);

private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();
	XMFLOAT3 mPosition;

private:
	Type				mType;
	std::string			mSprite;
};
