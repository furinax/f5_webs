#include "Tracker.h"

Tracker::Tracker()
{
	mOffset = Vec2f::zero();
	mScaleUpAdjust = Vec2f(1.1f, 1.1f);
}

Tracker::~Tracker()
{
	delete mBlobDetector;
	mImage.reset();
}

const std::list<ci::Vec2f> Tracker::getBlobCenters()
{
	return mBlobCenters;
}

void Tracker::setup()
{
	
	try {
		mCapture = Capture(
			getWindowWidth() < WEBCAM_MAX_WIDTH ? getWindowWidth() : WEBCAM_MAX_WIDTH,
			getWindowHeight() < WEBCAM_MAX_HEIGHT ? getWindowHeight() : WEBCAM_MAX_HEIGHT);
			Capture::findDeviceByName("Logitech HD Pro Webcam C910");
		mCapture.start();
	}
	catch (...) {
		console() << "Failed to initialize capture" << std::endl;
	}

	mScaleDown = 2.5f;
	mScaleUp = Vec2f(mScaleDown, mScaleDown);

	//this is the 2nd algorithm
	cv::SimpleBlobDetector::Params params;
	params.minThreshold = 2;
	params.maxThreshold = 255;
	params.thresholdStep = 5;

	params.minArea = 20; params.maxArea = 2000;
	params.minConvexity = 0.5f; params.maxConvexity = 1.f;
	//params.minInertiaRatio = .001f; params.maxInertiaRatio = 1.f;

	params.filterByConvexity = true;
	params.filterByArea = true;
	params.filterByColor = false;
	params.filterByCircularity = false;
	params.filterByInertia = false;
	
	mBlobDetector = new cv::SimpleBlobDetector(params);
	mBlobDetector->create("SimpleBlob");
}

Vec2f Tracker::adjustScale(Vec2f initialPoint)
{
	return getWindowCenter() + (initialPoint - getWindowCenter()) * mScaleUpAdjust;
}

void Tracker::mouseDown(Vec2f& mousePos)
{
	mOffset = mousePos - getWindowCenter();
}

void Tracker::update()
{
	if (mCapture && mCapture.checkNewFrame()) {
		mImage = mCapture.getSurface();
		mCaptureTex = gl::Texture(mImage);

		cv::Mat inputMat(toOcv(mImage));
		
		cv::cvtColor(inputMat, inputMat, CV_BGR2GRAY);
		cv::resize(inputMat, inputMat, cv::Size(((float)getWindowWidth()) / mScaleDown, ((float)getWindowHeight()) / mScaleDown));
		
		std::vector< cv::KeyPoint >  keyPoints;
		mBlobDetector->detect(inputMat, keyPoints);

		mBlobs.clear();
		mBlobs.reserve(keyPoints.size());
		for (int i = 0; i < keyPoints.size(); i++)
		{
			myBlob m;
			m.center = keyPoints[i].pt;
			m.radius = keyPoints[i].size;
			mBlobs.push_back(m);
		}

		if (mBlobs.size() > maxBlobs)
		{
			std::partial_sort(mBlobs.begin(), mBlobs.begin() + maxBlobs, mBlobs.end());
			mBlobs.resize(maxBlobs);
		}

		if (mBlobCenters.size() == maxBlobs)
		{
			mPrevCenters = mBlobCenters;
		}

		mBlobCenters.clear();
		std::for_each(mBlobs.begin(), mBlobs.end(), [&](myBlob &x) {mBlobCenters.push_back(adjustScale(fromOcv(x.center)*mScaleUp)); });
	}
	else
	{
		console() << "WARNING: skipped a frame: " << getElapsedFrames() << std::endl;
	}
}

void Tracker::draw()
{
	if (mCaptureTex) {
		gl::pushMatrices();
		gl::translate(mOffset);
		gl::draw(mCaptureTex);

		gl::color(Color::white());

		for (int i = 0; i < mBlobs.size(); i++)
		{
			Vec2f center = adjustScale(fromOcv(mBlobs[i].center)*mScaleUp);
			glBegin(GL_POINTS);
			glVertex2f(center);
			glEnd();
			glLineWidth(1.f);
			gl::drawStrokedCircle(center, mBlobs[i].radius);
		}

		gl::popMatrices();
		
		//draw a circle at the center to show offset
		gl::color(1.f, 0, 0);
		glBegin(GL_POINTS);
		glVertex2f(mOffset + getWindowCenter());
		glEnd();
		gl::drawStrokedCircle(mOffset + getWindowCenter(), 5.f);
	}
}