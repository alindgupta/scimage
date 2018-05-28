/**
 *  @file    matlabutils.hpp
 *  @author  Alind Gupta
 *  @date    May 27, 2018
 *  @version 0.1
 *  
 *  @brief Implementation of matlab utilities.
 *  @section DESCRIPTION
 *  None
 */

#ifndef matlabutils_hpp
#define matlabutils_hpp

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>

namespace matlabutils {
    
  const cv::Point GINPUT_DELIMITER(-1, -1);
    
  /**
   * std::vector wrapper that stores the number of delimiter values in ginput
   * to avoid O(n) counting when allocating a matrix for `improfile`.
   */
  struct GVector {
    std::vector<cv::Point> v;
    size_t count;
        
    GVector() : v(std::vector<cv::Point>()), count(0) {}
  };
    
   /**
     * @brief Return x,y coordinates from user input mouse clicks.
     *
     * Usage:
     * (1) Left mouse click will select point under mouse. 
     * (2) Right mouse click will remove last selected point.
     * (3) Left mouse click with SHIFT pressed will 
     * enter a token value of (-1, -1) into the userdata vector
     * serving as a delimiter between multiple instances of objects.
     *
     * @param event Mouse event
     * @param x x-coordinate
     * @param y y-coordinate
     * @param flags User-defined flags (unused)
     * @param userdata Void pointer to a std::vector<Point>
     * @return void
     */
  void ginput(int event, int x, int y, int flags, void* userdata);

   /**
     * @brief Calculate pixel profiles.
     *
     * @param vec Vector of points (x,y coordinates)
     * @param img Image as cv::Mat
     * @return std::vector<cv::Mat> one for each channel (i.e. RGB)
     * where each column represents linescans of one object of interest
     * i.e. values from ginput until a delimiter (GINPUT_DELIMTER or end of input)
     */
  std::vector<cv::Mat> improfile(const GVector& vec, const cv::Mat& img);

}

#endif /* matlabutils_hpp */
