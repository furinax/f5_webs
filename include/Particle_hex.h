#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Particle.h"
#include "cinder/gl/Texture.h"
#include "boost\shared_ptr.hpp"

class Particle_hex : public Particle{
public:
	Particle_hex(const std::list< ci::Vec2f > &vpos);
	void update(const std::list< ci::Vec2f > &vpos);
	void draw(const bool overlay, const std::list < ci::Vec2f> &vpos);
private:
	void drawHex(const int args_steps, const int offsetX, const int offsetY, const int width, const int height);
};