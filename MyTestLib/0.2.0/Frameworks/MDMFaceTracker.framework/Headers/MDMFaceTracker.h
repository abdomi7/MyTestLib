//
//  MDMFaceTracker.h
//  MoodMe
//
// Copyright (c) 2015 MoodMe (http://www.mood-me.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <MDMFaceTracker/MDMFaceFrame.h>
#import <MDMFaceTracker/FaceMeshGeometryConverter.h>


//! Project version number for MDMFaceTracker.
FOUNDATION_EXPORT double MDMFaceTrackerVersionNumber;

//! Project version string for MDMFaceTracker.
FOUNDATION_EXPORT const unsigned char MDMFaceTrackerVersionString[];

#define MDM MDMFaceTracker.sharedInstance


@protocol UpdatableScene <NSObject>

- (void)updateVideoTexture:(CVPixelBufferRef)texture;
- (void)updateSceneWithFace:(MDMFaceFrame *)face;

@end


@interface MDMFaceTracker : NSObject

+ (MDMFaceTracker *)sharedInstance;

@property id<UpdatableScene> delegate;
@property (nonatomic, readonly) BOOL faceTracked;

- (void)updateVideoFrame:(CVPixelBufferRef)frame timestamp:(NSTimeInterval)time withFieldOfView:(float)fieldOfView;

@end
