#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "ParticleSystem.h"
#include "ParticleFactory.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;

class f5_websApp : public AppNative {
  public:
	void setup();
	void update();
	void draw();

	void mouseDown(MouseEvent event);
	void mouseUp(MouseEvent event);
	void mouseMove(MouseEvent event);
	void mouseDrag(MouseEvent event);

	Vec2f mMousePosition, mPrevPosition;
	std::vector<ParticleSystem> pss;
	bool mParticlesVisible = true;
	ParticleFactory pf;
	params::InterfaceGl		mParams;
	int mTotalParticles = 0;
	bool mParamsVisible = true;
};

void f5_websApp::setup()
{
	setWindowSize(1280, 720);
	setFrameRate(30.f);
	gl::color(Color::black());

	ParticleSystem ps1;
	ps1.setup();
	pss.push_back(ps1);

	// Setup the parameters
	mParams = params::InterfaceGl("Parameters", Vec2i(200, 150));
	mParams.addParam("Particle ID", &pf.d_particleToCreate, "min=0 max=0 keyIncr=+ keyDecr=-");
	mParams.addSeparator();
	mParams.addParam("Total particles", &mTotalParticles, "readonly=1");
}

void f5_websApp::mouseUp(MouseEvent event)
{
	mPrevPosition = mMousePosition;
	mMousePosition = event.getPos();
}
void f5_websApp::mouseDown(MouseEvent event)
{
	mPrevPosition = mMousePosition;
	mMousePosition = event.getPos();
}
void f5_websApp::mouseDrag(MouseEvent event)
{
	mPrevPosition = mMousePosition;
	mMousePosition = event.getPos();
}

void f5_websApp::mouseMove(MouseEvent event)
{
	mPrevPosition = mMousePosition;
	mMousePosition = event.getPos();
}

void f5_websApp::update()
{
	int particleCount = 0;
	for (int i = 0; i < pss.size(); i++ )
	{
		pf.create(getElapsedSeconds(), mMousePosition, pss[i]);
		pss[i].update(mMousePosition);
		particleCount += pss[i].mParticles.size();
	}

	mTotalParticles = particleCount;
}

void f5_websApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	if (mParamsVisible)
		mParams.draw();

	
	if (mParticlesVisible)
	{
		for (int i = 0; i < pss.size(); i++)
			pss[i].draw( getWindowCenter());
	}
}

CINDER_APP_NATIVE( f5_websApp, RendererGl )
