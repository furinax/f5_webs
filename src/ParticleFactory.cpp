#include "ParticleFactory.h"
#include "cinder/gl/gl.h"
#include "ParticleTrack.h"

using namespace ci;
using namespace ci::app;

std::map< key_t, void(*)(const std::list< ci::Vec2f > &vpos, ParticleSystem &ps) > trackMap(mTrack, mTrack + map_start_values_size);

void ParticleFactory::create(const std::list< ci::Vec2f > &vpos, ParticleSystem & ps)
{

	switch (d_particleToCreate)
	{
		case PARTICLE_CIRCLE:{
			Particle* particle = new Particle_circle(vpos);
			ps.addParticle(particle);
		}break;
		default:
			ci::app::console() << "UNKNOWN PARTICLE: " << d_particleToCreate;
			break;
	}
}

void ParticleFactory::perform(const std::list< ci::Vec2f > &vpos, ParticleSystem & ps)
{
	double adjustedTime = getElapsedSeconds() + d_adjustSeconds - d_offsetTime;

	for (const element_t elem : mTrack)
	{
		if (adjustedTime >= elem.first.first && adjustedTime < elem.first.second)
			elem.second(vpos, ps);
	}

}