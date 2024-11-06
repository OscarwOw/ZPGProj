#pragma once
#include <vector>
#include "ILightObserver.h"
#include "LightSource.h"
class LightPublisher {
public:
	LightPublisher() {
	}

	void attachObserver(ILightObserver* lightObserver);
	void attachLightSource(LightSource* lightObserver);
	void publish();
private:
	std::vector<ILightObserver*> _observers;
	std::vector<LightSource*> _lightSources;
};
