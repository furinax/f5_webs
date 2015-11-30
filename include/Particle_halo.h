#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Particle.h"
#include "cinder/gl/Texture.h"
#include "boost\shared_ptr.hpp"

class Particle_halo : public Particle{
public:
	Particle_halo(const std::list< ci::Vec2f > &vpos);
	void update(const std::list< ci::Vec2f > &vpos);
	void draw(const bool overlay, const std::list< ci::Vec2f > &vpos);
private:
	void roundAngle(ci::Vec3f& pos, const float);
	int mMinRadius;
};