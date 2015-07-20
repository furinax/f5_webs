#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Particle.h"
#include "cinder/gl/Texture.h"
#include "boost\shared_ptr.hpp"

class Particle_spring : public Particle{
public:
	Particle_spring(const ci::Vec2f& position);
	void update(const ci::Vec2f pos);
};