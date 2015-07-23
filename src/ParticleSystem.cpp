#include "ParticleSystem.h"

using namespace ci;
using namespace ci::app;

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem(){
	for (std::vector<Particle*>::iterator it = mParticles.begin(); it != mParticles.end(); ++it){
		delete *it;
	}
	mParticles.clear();
}

void ParticleSystem::setup()
{
	gl::Fbo::Format format;
	format.enableMipmapping(false);
	format.setCoverageSamples(16);
	format.setSamples(4);

	mFbo = gl::Fbo(getWindowWidth(), getWindowHeight(), format); mFbo.getTexture().setFlipped(true);
	mFboBlurred = gl::Fbo(getWindowWidth(), getWindowHeight(), format); mFboBlurred.getTexture().setFlipped(true);
	mFboTemporary = gl::Fbo(getWindowWidth(), getWindowHeight(), format);

	blurShader = gl::GlslProg(loadResource(RES_BLUR_VERT),
		loadResource(RES_BLUR_FRAG));

}

void ParticleSystem::update(const std::list< ci::Vec2f > &vpos){
	
	for (std::vector<Particle*>::iterator it = mParticles.begin(); it != mParticles.end();){
		if ((*it)->mIsDead) {
			delete *it;
			it = mParticles.erase(it);
		}
		else {
			(*it)->update(vpos);
			++it;
		}
	}

}

void ParticleSystem::draw(const std::list< ci::Vec2f > &vpos){

	gl::enableAlphaBlending();

	for (std::vector<Particle*>::iterator it = mParticles.begin(); it != mParticles.end(); ++it){
		(*it)->draw(false, vpos);
	}
	

	mFboBlurred.bindFramebuffer();

	ColorA fade(0, 0, 0, 1.f);
	Rectf rect(0, 0, getWindowWidth(), getWindowHeight());
	gl::color(fade);
	gl::drawSolidRect(rect);

	gl::disableAlphaBlending();
	gl::color(Color::white());

	for (std::vector<Particle*>::iterator it = mParticles.begin(); it != mParticles.end(); ++it){
		(*it)->draw(false, vpos);
	}

	mFboBlurred.unbindFramebuffer();

	mFbo.bindFramebuffer();
	gl::draw(mFboBlurred.getTexture(), getWindowBounds());
	mFbo.unbindFramebuffer();

	blurShader.bind();
	blurShader.uniform("tex0", 0); // use mFboBlurred, see lower
	blurShader.uniform("sampleOffset", Vec2f(1.5f / 800.0f, 0.0f));

	mFboTemporary.bindFramebuffer();
	gl::clear(Color::black());
	mFboBlurred.bindTexture(0); // use rendered scene as texture
	gl::pushMatrices();
	gl::setMatricesWindow(getWindowWidth(), getWindowHeight(), false);
	gl::drawSolidRect(mFboBlurred.getBounds());
	gl::popMatrices();
	mFboBlurred.unbindTexture();
	mFboTemporary.unbindFramebuffer();

	blurShader.uniform("sampleOffset", Vec2f(0.0f, 1.5f / 600.0f));

	mFboBlurred.bindFramebuffer();
	gl::clear(Color::black());
	mFboTemporary.bindTexture(0); // use horizontally blurred scene as texture
	gl::pushMatrices();
	gl::setMatricesWindow(getWindowWidth(), getWindowHeight(), false);
	gl::drawSolidRect(mFboTemporary.getBounds());
	gl::popMatrices();
	mFboTemporary.unbindTexture();
	mFboBlurred.unbindFramebuffer();

	blurShader.unbind();

	gl::enableAdditiveBlending();
	for (int i = 0; i < mUnderlays; i++)
	{
		gl::color(Color::white());
		gl::draw(mFboBlurred.getTexture(), getWindowBounds());
	}

	for (std::vector<Particle*>::iterator it = mParticles.begin(); it != mParticles.end(); ++it){
		(*it)->draw(true, vpos);
	}

	gl::disableAlphaBlending();
	
}

void ParticleSystem::addParticle(Particle *particle){
	mParticles.push_back( particle );
}