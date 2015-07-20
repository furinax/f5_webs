#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Particle.h"
#include "cinder/gl/Texture.h"
#include "boost\shared_ptr.hpp"

class Particle_field : public Particle{
public:
	Particle_field(const ci::Vec2f& position);
	void update(const ci::Vec2f pos);
	void draw(const bool overlay, const ci::Vec2f pos);

	static int mThrottle;
	static const int mThrottleMax = 50;
};