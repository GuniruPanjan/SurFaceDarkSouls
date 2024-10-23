#pragma once
#include "ObjectBase.h"
class RectObject : public ObjectBase
{
public:
	RectObject(float width, float hight, float depth);
	~RectObject();

	void Init(std::shared_ptr<MyLibrary::Physics> physics, MyLibrary::LibVec3 pos, bool isEnter = false);
	void Update(MyLibrary::LibVec3 pos);

	void OnCollideEnter(const std::shared_ptr<Collidable>& collidable) {};

	void Finalize(const std::shared_ptr<MyLibrary::Physics> physics) override;

	void OnTriggerEnter(const std::shared_ptr<Collidable>& collidable) override;

	bool GetIsTrigger();

	void IsTriggerReset();

private:
	std::shared_ptr<MyLibrary::Physics> m_pPhysics;

	bool m_isEnter = false;
	bool m_isTriggerEnter = false;

};

