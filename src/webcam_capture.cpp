
//opencv
#include "opencv2/opencv.hpp"

//std
#include <iostream>
#include <cstdlib>

//Declaracion variable tamaño
const int dimension = 20;

int main(int argc, char *argv[]) 
{
	//OpenCV video capture object
    cv::VideoCapture camera;
	
	//OpenCV image object
    cv::Mat image;
	
	//camera id . Associated to device number in /dev/videoX
	int cam_id; 
	
	//pixel value (4-element vector)
	cv::Scalar_<unsigned char> px_value;
	
	//check user args
	switch(argc)
	{
		case 1: //no argument provided, so try /dev/video0
			cam_id = 0;  
			break; 
		case 2: //an argument is provided. Get it and set cam_id
			cam_id = atoi(argv[1]);
			break; 
		default: 
			std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl; 
			std::cout << "EXIT program." << std::endl; 
			break; 
	}
	
	//advertising to the user 
	std::cout << "Opening video device " << cam_id << std::endl;

    //open the video stream and make sure it's opened
    if( !camera.open(cam_id) ) 
	{
        std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
        return -1;
    }

    //capture loop. Out of user press a key
    while(1)
	{
		//Read image and check it. Blocking call up to a new image arrives from camera.
        if(!camera.read(image)) 
		{
            std::cout << "No frame" << std::endl;
            cv::waitKey();
        }

// Central Pixels */
    	// std::cout << "Central pixel is (" << image.cols/2 << "," << image.rows/2 << ")" << std::endl; */

    	int central_pixel_y = image.rows/2;

	int central_pixel_x = image.cols/2;

    	//Get pixel 3 channel values

	cv::Vec3b intensity = image.at<cv::Vec3b>(central_pixel_y, central_pixel_x);

	int blue = intensity.val[0];
	int green = intensity.val[1];
	int red = intensity.val[2];


	//Print image dimensions */
	std::cout<<"Image size is: "<<image.rows<<"x"<<image.cols<<std::endl;

	//Print central pixel coordinates
	std::cout<<"The central pixel is at: "<<central_pixel_y<<"x"<<central_pixel_x<<std::endl;

	//Print central pixel 3 original channel values
	std::cout<<"And its original 3 channel values are: "<<std::endl;
	std::cout<<"Blue: "<<blue<<" Green: "<<green<<" Red: "<<red<<std::endl;

	//Set black to the central pixel and its neighbors
		for (int y = central_pixel_y - dimension; y <= central_pixel_y + dimension; y ++) {
    
			for (int x = central_pixel_x - dimension; x <= central_pixel_x + dimension; x ++) {
	
	//Set circle condition: paints pixels satisfying this condition
				        
			if(pow(x-central_pixel_x,2)+pow(y-central_pixel_y,2)<=pow(dimension,2)){image.at<cv::Vec3b>(y, x) = 255;}
				
    			}
		}

        
        //show image in a window
        cv::imshow("Output Window", image);
		
		//print image dimensions
		std::cout << "image size is: " << image.rows << "x" << image.cols << std::endl; 
		std::cout << "image depth: " << image.depth() << std::endl; 
		std::cout << "num channels: " << image.channels() << std::endl; 
		px_value = image.at<cv::Scalar_<unsigned char> >(image.rows/2, image.cols/2, 0); 
		std::cout << "central pixel value (BGR): " << (int)px_value[0] << "," << (int)px_value[1] << "," << (int)px_value[2] << std::endl; 
		
		//Waits 1 millisecond to check if a key has been pressed. If so, breaks the loop. Otherwise continues.
        if(cv::waitKey(1) >= 0) break;
    }   
}
