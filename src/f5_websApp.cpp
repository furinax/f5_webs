#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "ParticleSystem.h"
#include "ParticleFactory.h"
#include "cinder/params/Params.h"
#include "cinder/Camera.h"

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
	//CameraPersp mCam;
	//Vec3f mEye, mCenter, mUp;
	//Quatf mSceneRotation;
};

void f5_websApp::setup()
{
	// SET WINDOW
	setWindowSize(1280, 720);
	setFrameRate(30.f);
	gl::color(Color::black());

	// SETUP CAMERA
	/*mEye		= Vec3f(0.f, 0.f, -500.f);
	mCenter		= Vec3f::zero();
	mUp			= Vec3f::yAxis();
	mCam.setPerspective(120.f, getWindowAspectRatio(), 5.0f, 3000.0f);*/

	// SETUP PARTICLE SYSTEMS
	ParticleSystem ps1;
	ps1.setup();
	pss.push_back(ps1);

	// SETUP PARAMS
	mParams = params::InterfaceGl("Parameters", Vec2i(200, 150));
	mParams.addParam("Particle ID", &pf.d_particleToCreate, "min=0 max=2 keyIncr=+ keyDecr=-");
	mParams.addSeparator();
	mParams.addParam("Total particles", &mTotalParticles, "readonly=1");
	//mParams.addParam("Scene Rotation", &mSceneRotation);
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
	// UPDATE CAMERA
	/*mCam.lookAt(mEye, mCenter, mUp);
	gl::setMatrices(mCam);
	gl::rotate(mSceneRotation);*/

	// UPDATE PARTICLE SYSTEMS
	int particleCount = 0;
	for (int i = 0; i < pss.size(); i++ )
	{
		pss[i].update(mMousePosition);
		pf.create(getElapsedSeconds(), mMousePosition, pss[i]);
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
			pss[i].draw( mMousePosition );
	}
}

CINDER_APP_NATIVE( f5_websApp, RendererGl )
