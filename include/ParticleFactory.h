#pragma once

#include "Particle.h"
#include "ParticleSystem.h"
#include "cinder/app/AppNative.h"
#include "Particle_circle.h"

enum particle_choice
{
	PARTICLE_CIRCLE, //0
};

class ParticleFactory
{
public:
	//create: for testing
	void create(const double elapsedSeconds, const ci::Vec2f center, ParticleSystem & ps);
	int d_particleToCreate = 0;
	double d_offsetTime = 0;
	double d_adjustSeconds = 0.f; //negative means delay the visuals, positive means speed them up

private:

};