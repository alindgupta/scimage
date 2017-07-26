/**
 
    tensorops.hpp
    Operations for matrix manipulations

    @todo       Implement circshift, crosscorr

    @author     fushitarazu
    @version    0.1
 
 */

#ifndef tensorops_hpp
#define tensorops_hpp

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

namespace tensorops
{
    void circshift();
    
    
    /**
     
     Based on the eponymous function in matlab
     Returns x,y coordinates from left mouse clicks to the setMouseCallback function
     
     Functionality
     - single left mouse click will select point under mouse
     - single right mouse click will remove last selected point
     - single left mouse click with SHIFT pressed will enter a token value of (-1, -1) into the userdata vector
     serving as a delimiter between multiple instances of objects
     
     
     */
     int crosscor(const cv::Mat& mat);
}



#endif /* tensorops_hpp */
