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
		}break;
		case PARTICLE_SPHERE:{
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
		case PARTICLE_QUEUE:{
			Particle* particle = new Particle_queue(vpos);
			ps.addParticle(particle);
		}break;
		case PARTICLE_TORRENT:{
			Particle* particle = new Particle_torrent(vpos);
			ps.addParticle(particle);
		}break;
		case PARTICLE_HEX:{
			Particle* particle = new Particle_hex(vpos);
			ps.addParticle(particle);
		}break;
		case PARTICLE_TRAIL:{
			Particle* particle = new Particle_trail( vpos );
			ps.addParticle(particle);
		}break;
		case PARTICLE_FFT:{
			Particle* particle = new Particle_fft(vpos);
			ps.addParticle(particle);
		}break;
		case PARTICLE_RIPPLE:{	
			Particle* particle = new Particle_ripple(vpos);
			ps.addParticle(particle);
		}break;
		case PARTICLE_PATH:{
			Particle* particle = new Particle_path(vpos);
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