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
		XMFLOAT3 rotation = getWorldRotation(); 
		return rotation.x; // Return the Pitch
	}
	float getYaw() const 
	{
		XMFLOAT3 rotation = getWorldRotation(); 
		return rotation.y; // Return the Yaw
	}
	float getRoll() const
	{
		XMFLOAT3 rotation = getWorldRotation();
		return rotation.z; // Return the Yaw
	}

private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();
	XMFLOAT3 mPosition;

	void updateCurrent(const GameTimer& gt);
private:
	Type				mType;
	std::string			mSprite;
};
