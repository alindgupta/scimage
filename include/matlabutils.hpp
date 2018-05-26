/**
 
    matlabutils.hpp
    Matlab-inspired interface for image processing using opencv3
    - ginput
    - improfile
 
    @author     fushitarazu
    @version    0.1
 
 */

#ifndef matlabutils_hpp
#define matlabutils_hpp

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>

namespace matlabutils {
    
    const cv::Point GINPUT_DELIMITER(-1, -1);
    
    /**
     
        Vector wrapper that stores the number of delimiter values in ginput
            to avoid O(n) counting when allocating a matrix for improfile
     
     */
    struct GVector
    {
        std::vector<cv::Point> v;
        size_t count;
        
        GVector()
        : v(std::vector<cv::Point>()), count(0) {}
        
    };
    

    /**
     
        Based on the eponymous function in matlab
        Returns x,y coordinates from left mouse clicks to the setMouseCallback function
        
        Functionality
        - single left mouse click will select point under mouse 
        - single right mouse click will remove last selected point
        - single left mouse click with SHIFT pressed will enter a token value of (-1, -1) into the userdata vector
            serving as a delimiter between multiple instances of objects
        
        @name ginput
     
        @param event        Mouse event  :: int
        @param x            x coordinate :: int
        @param y            y coordinate :: int
        @param flags        User flags (unused)
        @param userdata     Void pointer to a std::vector<Point>
     
     */
    void ginput(int event, int x, int y, int flags, void* userdata);


    /**
     
        Based on the eponymous function in matlab
        Basically a wrapper for line iterator functionality provided by opencv
        Takes a GVector filled using ginput and an image
     
        @name improfile
     
        @param vec          Vector of points (x,y coordinates)
        @param img          Image as a cv::Mat
        
        @return Vector of three cv::Mat, one for each channel (i.e. RGB)
                 where each column represents linescans of one object of interest
                 i.e. values from ginput until a delimiter (GINPUT_DELIMTER or end of input)
     
     */
    std::vector<cv::Mat> improfile(const GVector& vec, const cv::Mat& img);

    }

#endif /* matlabutils_hpp */
