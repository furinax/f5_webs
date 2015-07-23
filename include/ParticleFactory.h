#pragma once

#include "Particle.h"
#include "ParticleSystem.h"
#include "cinder/app/AppNative.h"
#include "Particle_circle.h"
#include "Particle_text.h"
#include "Particle_halo.h"
#include "Particle_horizon.h"
#include "Particle_helix.h"
#include "Particle_sphere.h"
#include "Particle_flat.h"
#include "Particle_field.h"
#include "Particle_spring.h"
#include "Particle_quad.h"

enum particle_choice
{
	PARTICLE_CIRCLE, //0
	PARTICLE_TEXT, //1
	PARTICLE_HALO, //2
	PARTICLE_HORIZON, //3
	PARTICLE_HELIX, //4
	PARTICLE_SPHERE, //5
	PARTICLE_FLAT, //6
	PARTICLE_FIELD, //7
	PARTICLE_SPRING, //8
	PARTICLE_QUAD, //9
};

class ParticleFactory
{
public:
	//create: for testing
	void create(const double elapsedSeconds, const std::list< ci::Vec2f > &vpos, ParticleSystem & ps);
	int d_particleToCreate = 9;
	double d_offsetTime = 0;
	double d_adjustSeconds = 0.f; //negative means delay the visuals, positive means speed them up

private:

};