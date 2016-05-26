#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "ParticleSystem.h"
#include "ParticleFactory.h"
#include "cinder/params/Params.h"
#include "cinder/Camera.h"
#include "Listener.h"
#include "Tracker.h"
#include "MusicPlayer.h"

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
	void keyDown(KeyEvent event);

	std::list< Vec2f > mMousePosition;
	std::vector<ParticleSystem> pss;
	bool mParticlesVisible = true;
	ParticleFactory pf;
	Tracker t;
	params::InterfaceGl		mParams;
	int mTotalParticles = 0;
	bool mParamsVisible = true;
	bool mTrackerVisible = false;
	bool mFullScreen = false;
	float mVolume = 0;
	MusicPlayer mMusicPlayer;
	//CameraPersp mCam;
	//Vec3f mEye, mCenter, mUp;
	//Quatf mSceneRotation;
};

void f5_websApp::setup()
{
	// SET WINDOW
	setWindowSize(1920, 1080);
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

	// SETUP LISTENER
	Listener& listener = Listener::getInstance();
	listener.setup();

	// SETUP TRACKER
	t.setup();

	// SETUP PARAMS
	mParams = params::InterfaceGl("Parameters", Vec2i(200, 150));
	mParams.addParam("Particle ID", &pf.d_particleToCreate, "keyIncr=+ keyDecr=-");
	mParams.addSeparator();
	mParams.addParam("Total particles", &mTotalParticles, "readonly=1");
	mParams.addParam("Volume", &mVolume, "readonly=1");
	mParams.addParam("Scale", &listener.mScale, "min=0.1 max=40.0 step=0.1");
	mParams.addParam("CenterX", &t.mOffset.x, "min=-200 max=200 step=5 keyIncr=D keyDecr=A");
	mParams.addParam("CenterY", &t.mOffset.y, "min=-200 max=200 step=5 keyIncr=W keyDecr=S");
	mParams.addParam("mScaleUpX", &t.mScaleUpAdjust.x, "min=0.00 max=2.00 step=0.05 keyIncr=r keyDecr=w");
	mParams.addParam("mScaleUpY", &t.mScaleUpAdjust.y, "min=0.00 max=2.00 step=0.05 keyIncr=t keyDecr=g");
	mParams.addParam("Tracker visible?", &mTrackerVisible, "");

	//mParams.addParam("Scene Rotation", &mSceneRotation);

	
}

void f5_websApp::mouseUp(MouseEvent event)
{
	mMousePosition = { event.getPos(), Vec2f(getWindowWidth() - event.getPos().x, getWindowHeight() - event.getPos().y ) };
}
void f5_websApp::mouseDown(MouseEvent event)
{
	mMousePosition = { event.getPos(), Vec2f(getWindowWidth() - event.getPos().x, getWindowHeight() - event.getPos().y) };
}
void f5_websApp::mouseDrag(MouseEvent event)
{
	mMousePosition = { event.getPos(), Vec2f(getWindowWidth() - event.getPos().x, getWindowHeight() - event.getPos().y) };
}

void f5_websApp::mouseMove(MouseEvent event)
{
	mMousePosition = { event.getPos(), Vec2f(getWindowWidth() - event.getPos().x, getWindowHeight() - event.getPos().y) };
}

void f5_websApp::keyDown(KeyEvent event)
{
	switch (event.getChar())
	{
	case 'x':
		mParamsVisible = !mParamsVisible;
		break;
	case 'd': //reset to default
		t.mOffset = Vec2f::zero();
		t.mScaleUpAdjust = Vec2f(1.f, 1.f);
		break;
	case 'f':
		mFullScreen = !mFullScreen;
		setFullScreen(mFullScreen);
		break;
	}
}

void f5_websApp::update()
{

//	if (!mMusicPlayer.mIsStarted )
//		mMusicPlayer.start();


	// UPDATE CAMERA
	/*mCam.lookAt(mEye, mCenter, mUp);
	gl::setMatrices(mCam);
	gl::rotate(mSceneRotation);*/

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

void f5_websApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	if (mParamsVisible)
		mParams.draw();

	if (mTrackerVisible)
		t.draw();
	
	if (mParticlesVisible)
	{
		for (int i = 0; i < pss.size(); i++)
			pss[i].draw(mMousePosition);
	}
}

CINDER_APP_NATIVE( f5_websApp, RendererGl )
