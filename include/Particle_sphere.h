#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Particle.h"
#include "cinder/gl/Texture.h"
#include "boost\shared_ptr.hpp"

class Particle_sphere : public Particle{
public:
	Particle_sphere(const std::list< ci::Vec2f > &vpos);
	void update(const std::list< ci::Vec2f > &vpos);
	void draw(const bool overlay, const std::list< ci::Vec2f > &vpos);
	bool isActive(const ci::Vec2f &lpos, const ci::Vec3f &rpos);
	void reAnchor();
};