#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Particle.h"
#include "cinder/gl/Texture.h"
#include "boost\shared_ptr.hpp"

class Particle_trail : public Particle{
public:
	Particle_trail(const std::list< ci::Vec2f > &vpos);
	void update(const std::list< ci::Vec2f > &vpos);
};