#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Particle.h"
#include "cinder/gl/Texture.h"
#include "boost\shared_ptr.hpp"

class Particle_sphere : public Particle{
public:
	Particle_sphere(const ci::Vec2f& position);
	void update(const ci::Vec2f pos);
};