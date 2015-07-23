#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Particle.h"
#include "cinder/gl/Texture.h"
#include "boost\shared_ptr.hpp"
#include "cinder/Channel.h"

class Particle_text : public Particle{
public:
	Particle_text(const std::list< ci::Vec2f > &vpos);
	void update(const std::list< ci::Vec2f > &vpos);

private:
	static cinder::Channel32f mChannel;
};