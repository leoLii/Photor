//
//  Transfer.h
//  Final Version
//
//  Created by Leo on 2016/12/26.
//  Copyright © 2016年 air711. All rights reserved.
//

#ifndef Transfer_h
#define Transfer_h
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <opencv2/highgui/highgui.hpp>
#import <opencv2/opencv.hpp>
#import <opencv2/core/core.hpp>
#import <opencv2/highgui.hpp>

@interface UIImage (OpenCv)

- (cv::Mat)CVMat;
- (cv::Mat)CVMat3;  // no alpha channel
- (cv::Mat)CVGrayscaleMat;


+ (UIImage *)imageWithCVMat:(const cv::Mat&)cvMat;
- (id)initWithCVMat:(const cv::Mat&)cvMat;




-(cv::Mat) cvMatFromUIImage: (const UIImage* ) image;
-(UIImage *) UIImageFromCVMat: (const cv::Mat&) cvMat;


-(IplImage *)CreateIplImageFromUIImage:(UIImage *)image;
-(UIImage *)UIImageFromIplImage:(IplImage *)image;

@end

#endif /* Transfer_h */
