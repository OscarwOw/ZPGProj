#include "LightPublisher.h"

void LightPublisher::attachObserver(ILightObserver* lightObserver)
{
	_observers.push_back(lightObserver);
}

void LightPublisher::attachLightSource(ILightEmitter* emitter)
{
	_lightEmitters.push_back(emitter);
}

void LightPublisher::publish()
{
	std::vector<LightData> data;
	for (ILightEmitter* lightSource : _lightEmitters) {
		data.push_back(lightSource->getLightData());
	}
	for (ILightObserver* observer : _observers) {
		observer->setLightsVector(data);
	}
}
