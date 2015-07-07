#include "ParticleFactory.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

void ParticleFactory::create(const double elapsedSeconds, const Vec2f origin, ParticleSystem & ps)
{

	switch (d_particleToCreate)
	{
		case PARTICLE_CIRCLE:{
			Particle* particle = new Particle_circle(origin);
			ps.addParticle(particle);
		}break;
		case PARTICLE_TEXT:{
			if (ps.mParticles.size() != 0)
				break;
			Particle* particle = new Particle_text(origin);
			ps.addParticle(particle);
			break;
		}
		case PARTICLE_HALO:{
			Particle* particle = new Particle_halo(origin);
			ps.addParticle(particle);
		}break;
		default:
			ci::app::console() << "UNKNOWN PARTICLE: " << d_particleToCreate;
			break;
	}
}