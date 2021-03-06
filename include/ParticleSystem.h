#pragma once

#include "Particle.h"
#include "cinder/Vector.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/app/AppNative.h"
#include "Resources.h"
#include <list>
#include <map>

class ParticleSystem{
public:
	ParticleSystem();
	~ParticleSystem();

	void setup();
	void update(const std::list< ci::Vec2f > &vpos);
	void draw(const std::list< ci::Vec2f > &vpos);

	void addParticle(Particle *particle);

	std::vector<Particle*> mParticles;
	ci::gl::Fbo mFboBlurred, mFboTemporary, mFbo;
	ci::gl::GlslProg blurShader;
	int mOrientation = 1;
	int mUnderlays = 3;
};