#include "ParticleFactory.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

void ParticleFactory::create(const double elapsedSeconds, const std::list< ci::Vec2f > &vpos, ParticleSystem & ps)
{

	switch (d_particleToCreate)
	{
		case PARTICLE_CIRCLE:{
			Particle* particle = new Particle_circle(vpos);
			ps.addParticle(particle);
		}break;
		case PARTICLE_TEXT:{
			if (ps.mParticles.size() != 0)
				break;
			Particle* particle = new Particle_text(vpos);
			ps.addParticle(particle);
			break;
		}
		case PARTICLE_HALO:{
			Particle* particle = new Particle_halo(vpos);
			ps.addParticle(particle);
		}break;
		case PARTICLE_HORIZON:{
			Particle* particle = new Particle_horizon(vpos);
			ps.addParticle(particle);
		}break;
		case PARTICLE_HELIX:{
			Particle* particle = new Particle_helix(vpos);
			ps.addParticle(particle);
			Particle* particleMirror = new Particle_helix(vpos);
		particleMirror->mOrientation = M_PI;
		ps.addParticle(particleMirror);
		}break;
		case PARTICLE_SPHERE:{
			if (ps.mParticles.size() != 0)
				break;
			Particle* particle = new Particle_sphere(vpos);
			ps.addParticle(particle);
		}break;
		case PARTICLE_FLAT:{
			Particle* particle = new Particle_flat(vpos);
			ps.addParticle(particle);
		}break;
		case PARTICLE_FIELD:{
			Particle* particle = new Particle_field(vpos);
			if (Particle_field::mThrottle-- == Particle_field::mThrottleMax)
				ps.addParticle(particle);
			else if (Particle_field::mThrottle <= 0)
				Particle_field::mThrottle = Particle_field::mThrottleMax;
		}break;
		case PARTICLE_SPRING:{
			Particle* particle = new Particle_spring(vpos);
			ps.addParticle(particle);
		}break;
		case PARTICLE_QUAD:{
			Particle* particle = new Particle_quad(vpos);
			ps.addParticle(particle);
		}break;
		default:
			ci::app::console() << "UNKNOWN PARTICLE: " << d_particleToCreate;
			break;
	}
}