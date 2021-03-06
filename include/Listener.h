#pragma once

#include "cinder/app/AppNative.h"

#include "cinder/audio/MonitorNode.h"
#include "cinder/audio/Utilities.h"
#include "cinder/Vector.h"

class Listener
{
public:
	void setup();
	static Listener& getInstance()
	{
		static Listener instance;
		return instance;
	}

	void update();
	float getVolume() const;
	float getBinVolume(const int bin) const;
	int getBinForFrequency(const int freq) const;

	ci::audio::InputDeviceNodeRef		mInputDeviceNode;
	ci::audio::MonitorSpectralNodeRef	mMonitorSpectralNode;
	std::vector<float>					mMagSpectrum;
	float mScale;
	float outVolume; // temporary var so we can output it from the params

private:
	Listener() {};

	Listener(Listener const&) = delete;
	void operator=(Listener const&) = delete;
};