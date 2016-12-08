#include <map>
#include <utility>
#include "ParticleSystem.h"
#include "ParticleFactory.h"

#include "Particle_circle.h"


typedef std::pair<float, float> key_t;
typedef std::pair<key_t, void(*)(const std::list< ci::Vec2f > &vpos, ParticleSystem &ps) > element_t;
typedef std::map< key_t, void(*)(const std::list< ci::Vec2f > &vpos, ParticleSystem &ps) > map_t;

const element_t mTrack[] = {

		element_t(key_t(0.f, 44.f), [](const std::list< ci::Vec2f > &vpos, ParticleSystem &ps){ //intro vis
		Particle* particle = new Particle_circle(vpos);
		ps.addParticle(particle);
	})

};

const int map_start_values_size = sizeof(mTrack) / sizeof(mTrack[0]);

extern std::map <key_t, void(*)(const std::list< ci::Vec2f > &vpos, ParticleSystem &ps) > trackMap;