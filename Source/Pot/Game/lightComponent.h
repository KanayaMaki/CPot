#pragma once

#include "./Pot/Game/updater.h"

#include "./Pot/Render/light.h"

namespace cpot {

class LightComponent : public Updater {
	CPOT_TYPE(LightComponent, Updater)

public:
	LightComponent();
	~LightComponent();

	virtual Light* GetLight() const = 0;
};


class DirectionalLightComponent : public LightComponent {
	CPOT_TYPE(DirectionalLightComponent, LightComponent)

public:
	void OnUpdate() override {
		
	}

	Light* GetLight() const override {
		return (Light*)(&mDirectionalLight);
	}

public:
	DirectionalLight mDirectionalLight;
};


class LightComponentManager : public Updater, public Singleton<LightComponentManager> {
	friend class LightComponent;

private:
	void Regist(LightComponent* l) {
		mLight.PushBack(l);
	}
	void Remove(LightComponent* l) {
		mLight.Remove(l);
	}

public:
	LightComponent* Get(u32 aIndex) {
		return mLight[aIndex];
	}

public:
	void OnUpdate() override {
		for (u32 i = 0; i < mLight.GetSize(); i++) {
			LightManager::S().SetLight(mLight[i]->GetLight(), i);
		}
	}

private:
	Vector<LightComponent*> mLight;
};

}