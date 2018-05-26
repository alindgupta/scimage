/**
 *  @file    matlabutils.cpp
 *  @author  Alind Gupta
 *  @date    May 26, 2018
 *  @version 0.1
 *  
 *  @brief Implementation of matlab utilities.
 *  @section DESCRIPTION
 *  None
 */
 
#include "matlabutils.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using mt = matlabutils;

/** 
  *  @brief Get coordinates of user-defined points. 
  *  
  *  @param event
  *  @param x
  *  @param y
  *  @param flags
  *  @param userdata
  *  @return void
  */ 
void mt::ginput(int event, int x, int y, int flags, void *userdata) {
  // check userdata for null pointer
  if (!userdata) {
    std::cerr << "A null pointer was provided for user data!\n";
    return;
  }
    
  // require void pointer to be castable to GVector
  // do not use a C-style cast
  auto vec = static_cast<mt::GVector*>(userdata);
    
  if (event == cv::EVENT_LBUTTONDOWN && flags == 1) {
    vec->v.push_back(cv::Point(x, y));
  }
  else if (event == cv::EVENT_RBUTTONDOWN) {
    if (!vec->v.empty()) {
      vec->v.pop_back();
    }
  }
  else if (event == cv::EVENT_LBUTTONDOWN && flags != 1) {
    vec->v.push_back(mt::GINPUT_DELIMITER);
    vec->count++;
  }
}

/** 
  *  @brief Generate pixel profiles given a set of (user-defined) 
  *  image coordinates.
  *  
  *  @param vec
  *  @param img
  *  @return std::vector<cv::Mat> of pixel values, 
  *  where elements correspond to rgb channels.
  */ 
std::vector<cv::Mat> mt::improfile(const mt::GVector& vec,
                                   const cv::Mat& img) {

  const int MAX_PX_LENGTH = 100;
    
  // initialize a vector of cv::Mat of size 3 for each channel
  cv::Mat r(MAX_PX_LENGTH, static_cast<int>(vec.count+1),
            CV_8U, cv::Scalar(0.0));
  cv::Mat g(MAX_PX_LENGTH, static_cast<int>(vec.count+1),
            CV_8U, cv::Scalar(0.0));
  cv::Mat b(MAX_PX_LENGTH, static_cast<int>(vec.count+1),
            CV_8U, cv::Scalar(0.0));
  std::vector<cv::Mat> mat = {r, g, b};
    
  // utility unwrapper
  auto v = vec.v;
    
  // number of objects
  int objectID = 0;
    
  // line iterator
  for (int i = 0; i < v.size() - 1; i++) {
        
    auto px1 = v[i];
    auto px2 = v[i+1];
        
    if (px1 == GINPUT_DELIMITER) {
      objectID++;
      continue;
    }
        
    if (px2 == GINPUT_DELIMITER) {
      objectID++;
      continue;
    }
        
    cv::LineIterator it(img, px1, px2, 8);
    cv::Vec3b buffer;
        
    for (int j = 0; j < it.count; j++, ++it) {
      buffer = static_cast<const cv::Vec3b>(*it);
      mat[0].at<uchar>(j, objectID) = buffer.val[0];
      mat[1].at<uchar>(j, objectID) = buffer.val[1];
      mat[2].at<uchar>(j, objectID) = buffer.val[2];
    }
  }
    
  return mat;
}

