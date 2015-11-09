#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Particle.h"
#include "cinder/gl/Texture.h"
#include "boost\shared_ptr.hpp"

class Particle_torrent : public Particle{
public:
	Particle_torrent(const std::list< ci::Vec2f > &vpos);
	void update(const std::list< ci::Vec2f > &vpos);
};