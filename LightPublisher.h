#pragma once
#include <vector>
#include "ILightObserver.h"
#include "LightSource.h"
class LightPublisher {
public:
	LightPublisher() {
	}

	void attachObserver(ILightObserver* lightObserver);
	void attachLightSource(ILightEmitter* lightObserver);
	void publish();
private:
	std::vector<ILightObserver*> _observers;
	std::vector<ILightEmitter*> _lightEmitters;
};
