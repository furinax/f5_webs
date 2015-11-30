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
#include "Particle_queue.h"
#include "Particle_torrent.h"
#include "Particle_hex.h"
#include "Particle_trail.h"
#include "Particle_fft.h"
#include "Particle_fixed.h"

enum particle_choice
{
	PARTICLE_CIRCLE, //0
	PARTICLE_TEXT, //1
	PARTICLE_HALO, //2
	PARTICLE_HORIZON, //3 red shear
	PARTICLE_HELIX, //4 rising hexes
	PARTICLE_SPHERE, //5 two nest circles
	PARTICLE_FLAT, //6 grid lines
	PARTICLE_FIELD, //7 moving volume lines
	PARTICLE_SPRING, //8 circles
	PARTICLE_QUAD, //9 swirls
	PARTICLE_QUEUE, //10 zooming lines
	PARTICLE_TORRENT, //11 neural network
	PARTICLE_HEX, //12 expanding spiral
	PARTICLE_TRAIL, //13 simple history
	PARTICLE_FFT, //14 bars
	PARTICLE_FIXED //15 square turns
};

class ParticleFactory
{
public:
	//create: for testing
	void create(const double elapsedSeconds, const std::list< ci::Vec2f > &vpos, ParticleSystem & ps);
	int d_particleToCreate = 2;
	double d_offsetTime = 0;
	double d_adjustSeconds = 0.f; //negative means delay the visuals, positive means speed them up

private:

};