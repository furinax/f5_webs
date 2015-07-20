#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Particle.h"
#include "cinder/gl/Texture.h"
#include "boost\shared_ptr.hpp"
#include "cinder/Channel.h"

class Particle_text : public Particle{
public:
	Particle_text(const ci::Vec2f& position);
	void update(const ci::Vec2f pos);

private:
	static cinder::Channel32f mChannel;
};