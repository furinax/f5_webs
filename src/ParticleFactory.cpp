#include "ParticleFactory.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

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
		case PARTICLE_FIXED:{
			for (auto pos : vpos)
			{		
				Particle* particle = new Particle_fixed(std::list < Vec2f > {pos});
				ps.addParticle(particle);
			}
		}break;
		default:
			ci::app::console() << "UNKNOWN PARTICLE: " << d_particleToCreate;
			break;
	}
}

void ParticleFactory::perform(const std::list< ci::Vec2f > &vpos, ParticleSystem & ps)
{
	double adjustedTime = getElapsedSeconds() + d_adjustSeconds - d_offsetTime;
	if (adjustedTime < 0)
		ci::app::console() << "waiting for song to start..." << std::endl;

	if (adjustedTime >= 0 && adjustedTime < 20 && ps.mParticles.size() == 0)
	{
		Particle* particle = new Particle_text(vpos);
		ps.addParticle(particle);
	}

	if ( adjustedTime >= 0 && adjustedTime < 42 )
	{
		Particle* particle = new Particle_hex(vpos);
		ps.addParticle(particle);
		particle = new Particle_trail(vpos);
		ps.addParticle(particle);
	}
	if (adjustedTime >= 42 && adjustedTime < 90)
	{
		Particle* particle = new Particle_circle(vpos);
		ps.addParticle(particle);
	}
	if (adjustedTime >= 90 && adjustedTime < 120)
	{
		Particle* particle = new Particle_queue(vpos);
		ps.addParticle(particle);
	}
	if (adjustedTime >= 120 && adjustedTime < 150) // 2:00-2:30
	{
		Particle* particle = new Particle_spring(vpos);
		ps.addParticle(particle);
		particle = new Particle_horizon(vpos);
		ps.addParticle(particle);
	}

	if (adjustedTime >= 150 && adjustedTime < 180) // 2:30 - 3:00
	{
		Particle* particle = new Particle_flat(vpos);
		ps.addParticle(particle);
	}

	if (adjustedTime >= 180 && adjustedTime < 210) //3:00-3:30
	{
		Particle* particle = new Particle_sphere(vpos);
		ps.addParticle(particle);
	}

	if (adjustedTime >= 210 && adjustedTime < 240) //3:30-4:00
	{
		Particle* particle = new Particle_helix(vpos);
		ps.addParticle(particle);
	}

	if (adjustedTime >= 240 && adjustedTime < 255) //4:00-4:15
	{
		Particle* particle = new Particle_trail(vpos);
		ps.addParticle(particle);
	}

	if (adjustedTime >= 255 && adjustedTime < 285) //4:15-4:45
	{
		Particle* particle = new Particle_torrent(vpos);
		ps.addParticle(particle);
	}
}