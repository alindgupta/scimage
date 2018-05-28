/**
 *  @file    tensorops.hpp
 *  @author  Alind Gupta
 *  @date    May 27, 2018
 *  @version 0.1
 *  
 *  @brief None
 *  @section DESCRIPTION
 *  None
 */

#ifndef tensorops_hpp
#define tensorops_hpp

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

namespace tensorops {
  
  double xcorr(const cv::Mat&);
  cv::Mat finddelays(const cv::Mat&);
  cv::Mat circshift(const cv::Mat&, const std::vector<int>&);
};    


#endif /* tensorops_hpp */
