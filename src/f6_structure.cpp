#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "ParticleSystem.h"
#include "ParticleFactory.h"
#include "cinder/params/Params.h"
#include "cinder/Camera.h"
#include "Listener.h"

using namespace ci;
using namespace ci::app;

class f6_structure : public AppNative {
  public:
	void setup();
	void update();
	void draw();

	void mouseDown(MouseEvent event);
	void mouseUp(MouseEvent event);
	void mouseMove(MouseEvent event);
	void mouseDrag(MouseEvent event);
	void keyDown(KeyEvent event);

	std::list< Vec2f > mMousePosition;
	std::vector<ParticleSystem> pss;
	bool mParticlesVisible = true;
	ParticleFactory pf;
	params::InterfaceGl		mParams;
	int mTotalParticles = 0;
	bool mParamsVisible = false;
	bool mFullScreen = false;
	float mVolume = 0;

};

void f6_structure::setup()
{
	// SET WINDOW
	setWindowSize(1920, 1080);
	setFrameRate(30.f);
	gl::color(Color::black());

	// SETUP PARTICLE SYSTEMS
	ParticleSystem ps1;
	ps1.setup();
	pss.push_back(ps1);

	// SETUP LISTENER
	Listener& listener = Listener::getInstance();
	listener.setup();

	// SETUP TRACKER
	//t.setup();

	// SETUP PARAMS
	mParams = params::InterfaceGl("Parameters", Vec2i(200, 150));
	mParams.addParam("Particle ID", &pf.d_particleToCreate, "keyIncr=+ keyDecr=-");
	mParams.addSeparator();
	mParams.addParam("Total particles", &mTotalParticles, "readonly=1");
	mParams.addParam("Volume", &mVolume, "readonly=1");
	mParams.addParam("Scale", &listener.mScale, "min=0.1 max=40.0 step=0.1");
	
}

void f6_structure::mouseUp(MouseEvent event)
{
	mMousePosition = { event.getPos(), Vec2f(getWindowWidth() - event.getPos().x, getWindowHeight() - event.getPos().y ) };
}
void f6_structure::mouseDown(MouseEvent event)
{
	mMousePosition = { event.getPos(), Vec2f(getWindowWidth() - event.getPos().x, getWindowHeight() - event.getPos().y) };
}
void f6_structure::mouseDrag(MouseEvent event)
{
	mMousePosition = { event.getPos(), Vec2f(getWindowWidth() - event.getPos().x, getWindowHeight() - event.getPos().y) };
}

void f6_structure::mouseMove(MouseEvent event)
{
	mMousePosition = { event.getPos(), Vec2f(getWindowWidth() - event.getPos().x, getWindowHeight() - event.getPos().y) };
}

void f6_structure::keyDown(KeyEvent event)
{
	switch (event.getChar())
	{
	case 'x':
		mParamsVisible = !mParamsVisible;
		break;
	case 'f':
		mFullScreen = !mFullScreen;
		setFullScreen(mFullScreen);
		break;
	}
}

void f6_structure::update()
{

	// UPDATE TRACKER
	//t.update();

	// UPDATE LISTENER
	Listener& listener = Listener::getInstance();
	listener.update();
	mVolume = listener.getVolume();

	// UPDATE PARTICLE SYSTEMS
	int particleCount = 0;
	for (int i = 0; i < pss.size(); i++ )
	{

		pss[i].update(mMousePosition);
		pf.create(mMousePosition, pss[i]);
		particleCount += pss[i].mParticles.size();
	}
	mTotalParticles = particleCount;
}

void f6_structure::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	if (mParamsVisible)
		mParams.draw();
	
	if (mParticlesVisible)
	{
		for (int i = 0; i < pss.size(); i++)
			pss[i].draw(mMousePosition);
	}
}

CINDER_APP_NATIVE( f6_structure, RendererGl )
