#include <map>
#include <utility>
#include "ParticleSystem.h"
#include "ParticleFactory.h"

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
#include "Particle_ripple.h"
#include "Particle_path.h"

typedef std::pair<float, float> key_t;
typedef std::pair<key_t, void(*)(const std::list< ci::Vec2f > &vpos, ParticleSystem &ps) > element_t;
typedef std::map< key_t, void(*)(const std::list< ci::Vec2f > &vpos, ParticleSystem &ps) > map_t;

const element_t mTrack[] = {

	element_t(key_t(0.f, 20.f), [](const std::list< ci::Vec2f > &vpos, ParticleSystem &ps){ //intro title
		if (ps.mParticles.size() == 0)
		{
			Particle* particle = new Particle_text(vpos);
			ps.addParticle(particle);
		}
	}),

		element_t(key_t(0.f, 44.f), [](const std::list< ci::Vec2f > &vpos, ParticleSystem &ps){ //intro vis
		Particle* particle = new Particle_hex(vpos);
		ps.addParticle(particle);
		particle = new Particle_trail(vpos);
		ps.addParticle(particle);
	}),

		element_t(key_t(44.f, 46.f), [](const std::list< ci::Vec2f > &vpos, ParticleSystem &ps){  //transition between initial buildup and start of song
		Particle* particle = new Particle_queue(vpos);
		ps.addParticle(particle);
		particle = new Particle_torrent(vpos);
		ps.addParticle(particle);
	}),

		element_t(key_t(46.f, 90.f), [](const std::list< ci::Vec2f > &vpos, ParticleSystem &ps){  //main intro, loud
		Particle* particle = new Particle_circle(vpos);
		ps.addParticle(particle);
		particle = new Particle_ripple(vpos);
		ps.addParticle(particle);
	}),

		element_t(key_t(90.f, 120.f), [](const std::list< ci::Vec2f > &vpos, ParticleSystem &ps){  //slow vocals
		Particle* particle = new Particle_quad(vpos);
		ps.addParticle(particle);
	}),

		element_t(key_t(120.f, 150.f), [](const std::list< ci::Vec2f > &vpos, ParticleSystem &ps){  // 2:00-2:30
		Particle* particle = new Particle_spring(vpos);
		ps.addParticle(particle);
	}),

		element_t(key_t(150.f, 180.f), [](const std::list< ci::Vec2f > &vpos, ParticleSystem &ps){  // 2:30 - 3:00
		Particle* particle = new Particle_flat(vpos);
		ps.addParticle(particle);
	}),
		element_t(key_t(179.f, 184.f), [](const std::list< ci::Vec2f > &vpos, ParticleSystem &ps){  // 2:59 - 3:01
		Particle* particle = new Particle_halo(vpos);
		ps.addParticle(particle);
	}),
		element_t(key_t(181.f, 210.f), [](const std::list< ci::Vec2f > &vpos, ParticleSystem &ps){  //3:01-3:30
		Particle* particle = new Particle_sphere(vpos);
		ps.addParticle(particle);
		particle = new Particle_horizon(vpos);
		ps.addParticle(particle);
	}),
		element_t(key_t(210.f, 240.f), [](const std::list< ci::Vec2f > &vpos, ParticleSystem &ps){  //3:30-4:00
		Particle* particle = new Particle_sphere(vpos);
		ps.addParticle(particle);
		
		particle = new Particle_helix(vpos);
		ps.addParticle(particle);
	}),
		element_t(key_t(240.f, 255.f), [](const std::list< ci::Vec2f > &vpos, ParticleSystem &ps){  //4:00-4:15
		Particle* particle = new Particle_halo(vpos);
		ps.addParticle(particle);
	}),

		element_t(key_t(255.f, 285.f), [](const std::list< ci::Vec2f > &vpos, ParticleSystem &ps){  //4:15-4:45
		Particle* particle = new Particle_path(vpos);
		ps.addParticle(particle);
	}),
		

};

/*


if ( adjustedTime >= 0 && adjustedTime < 42 )
{

}
if (adjustedTime >= 42 && adjustedTime < 43) //transition between initial buildup and start of song
{
Particle* particle = new Particle_queue(vpos);
ps.addParticle(particle);
particle = new Particle_torrent(vpos);
ps.addParticle(particle);
}

if (adjustedTime >= 42 && adjustedTime < 90) //main intro, loud
{
Particle* particle = new Particle_circle(vpos);
ps.addParticle(particle);
particle = new Particle_ripple(vpos);
ps.addParticle(particle);
}

if (adjustedTime >= 90 && adjustedTime < 120) //slow vocals
{
Particle* particle = new Particle_quad(vpos);
ps.addParticle(particle);
}
if (adjustedTime >= 120 && adjustedTime < 150) // 2:00-2:30
{
Particle* particle = new Particle_spring(vpos);
ps.addParticle(particle);

}

if (adjustedTime >= 179 && adjustedTime < 180) // 2:59 - 3:00
{
// particle = new Particle_ripple(vpos);
//ps.addParticle(particle);
Particle* particle = new Particle_path(vpos);
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
Particle* particle = new Particle_sphere(vpos);
ps.addParticle(particle);
if (int(adjustedTime*2) % 6 == 0)
{
Particle* particle = new Particle_helix(vpos);
ps.addParticle(particle);
}
}

if (adjustedTime >= 240 && adjustedTime < 255) //4:00-4:15
{
Particle* particle = new Particle_trail(vpos);
ps.addParticle(particle);
particle = new Particle_halo(vpos);
ps.addParticle(particle);
}

if (adjustedTime >= 255 && adjustedTime < 285) //4:15-4:45
{
Particle* particle = new Particle_horizon(vpos);
ps.addParticle(particle);
}*/

const int map_start_values_size = sizeof(mTrack) / sizeof(mTrack[0]);

extern std::map <key_t, void(*)(const std::list< ci::Vec2f > &vpos, ParticleSystem &ps) > trackMap;