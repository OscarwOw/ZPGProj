#include "LightPublisher.h"

void LightPublisher::attachObserver(ILightObserver* lightObserver)
{
	_observers.push_back(lightObserver);
}

void LightPublisher::attachLightSource(LightSource* source)
{
	_lightSources.push_back(source);
}

void LightPublisher::publish()
{
	std::vector<LightData> data;
	for (LightSource* lightSource : _lightSources) {
		data.push_back(lightSource->getLightData());
	}
	for (ILightObserver* observer : _observers) {
		observer->setLightsVector(data);
	}
}
