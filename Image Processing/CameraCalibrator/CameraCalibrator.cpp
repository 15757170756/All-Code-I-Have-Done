#include "CameraCalibrator.h"
using namespace std;
using namespace cv;
// Open chessboard images and extract corner points
int CameraCalibrator::addChessboardPoints(
         const std::vector<std::string> &filelist, 
         cv::Size &boardSize) 
{
	cout << "boardSize: " << boardSize;
	// the points on the chessboard
	cv::Point2f wkk;               
	//cv::OutputArray wkk2;
	std::vector<cv::Point2f> corners;
	std::vector<cv::Point2f> imageCorners;
    std::vector<cv::Point3f> objectCorners;

    // 3D Scene Points:
    // Initialize the chessboard corners 
    // in the chessboard reference frame
	// The corners are at 3D location (X,Y,Z)= (i,j,0)
	cout << "boardSize.height: " << boardSize.height << endl;
	cout << "boardSize.width: " << boardSize.width << endl;
	for (int i=0; i<boardSize.height; i++) {
		for (int j=0; j<boardSize.width; j++) {
			objectCorners.push_back(cv::Point3f(i, j, 0.0f));
		}
    }

    // 2D Image points:
    cv::Mat image1; // to contain chessboard image
    int successes = 0;
    // for all viewpoints
    for (int i=0; i<filelist.size(); i++) 
	{

        // Open the image
        image1 = cv::imread(filelist[i],0);
		cout << "filelist:" << filelist[i] << endl;
		//cout << "image: " << image << endl;
        
		// Get the chessboard corners
		bool found = cv::findChessboardCorners(image1, boardSize, imageCorners, cv::CALIB_CB_ADAPTIVE_THRESH |
			cv::CALIB_CB_NORMALIZE_IMAGE);
		
		if (found == 1)
		{  
			cout << "found: " << found << endl;
			/*cout << "imageCorners: " << imageCorners << endl;*/
		}// Get subpixel accuracy on the corners

        cv::cornerSubPix(image1, imageCorners, 
                  cv::Size(5,5), 
                  cv::Size(-1,-1), 
			cv::TermCriteria(cv::TermCriteria::MAX_ITER +
                          cv::TermCriteria::EPS, 
             30,		// max number of iterations 
             0.1));     // min accuracy

          // If we have a good board, add it to our data
		  if (imageCorners.size() == boardSize.area()) {

			// Add image and scene points from one view
            addPoints(imageCorners, objectCorners);
            successes++;
          }

        //Draw the corners
        cv::drawChessboardCorners(image1, boardSize, imageCorners, found);
        cv::imshow("Corners on Chessboard", image1);
        cv::waitKey(2000);
    }

	return successes;
}

// Add scene points and corresponding image points
void CameraCalibrator::addPoints(const std::vector<cv::Point2f>& imageCorners, const std::vector<cv::Point3f>& objectCorners) {

	// 2D image points from one view
	imagePoints.push_back(imageCorners);          
	// corresponding 3D scene points
	objectPoints.push_back(objectCorners);
}

// Calibrate the camera
// returns the re-projection error
double CameraCalibrator::calibrate(cv::Size &imageSize)
{
	// undistorter must be reinitialized
	mustInitUndistort= true;

	//Output rotations and translations
   // std::vector<cv::Mat> rvecs, tvecs;

	// start calibration
	return 
     calibrateCamera(objectPoints, // the 3D points
		            imagePoints,  // the image points
					imageSize,    // image size
					cameraMatrix, // output camera matrix
					distCoeffs,   // output distortion matrix
					rotateVectors, translationVectors, // Rs, Ts 
					flag);        // set options
//					,CV_CALIB_USE_INTRINSIC_GUESS);

}

// remove distortion in an image (after calibration)
cv::Mat CameraCalibrator::remap(const cv::Mat &image) {

	cv::Mat undistorted;
	cout << "mustInitUndistort: " << mustInitUndistort << endl;
	if (mustInitUndistort) { // called once per calibration
    
		cv::initUndistortRectifyMap(
			cameraMatrix,  // computed camera matrix
            distCoeffs,    // computed distortion matrix
            cv::Mat(),     // optional rectification (none) 
			cv::Mat(),     // camera matrix to generate undistorted
			//cv::Size(576, 384),
            image.size(),  // size of undistorted
            CV_32FC1,      // type of output map
            map1, map2);   // the x and y mapping functions

		mustInitUndistort= false;
	}

	// Apply mapping functions
    cv::remap(image, undistorted, map1, map2, 
		cv::INTER_LINEAR); // interpolation type

	return undistorted;
}


// Set the calibration options
// 8radialCoeffEnabled should be true if 8 radial coefficients are required (5 is default)
// tangentialParamEnabled should be true if tangeantial distortion is present
void CameraCalibrator::setCalibrationFlag(bool radial8CoeffEnabled, bool tangentialParamEnabled) {

    // Set the flag used in cv::calibrateCamera()
    flag = 0;
    if (!tangentialParamEnabled) 
		flag += CV_CALIB_ZERO_TANGENT_DIST;

	if (radial8CoeffEnabled) 
		flag += CV_CALIB_RATIONAL_MODEL;
}



