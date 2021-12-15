//
//  MDMFaceFrame.h
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
#import <UIKit/UIKit.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Defines face regions to query the transforms for. Left and right are defined relative to the
 * person that the mesh belongs to. To retrieve the center transform use |centerTransform|.
 */
typedef NS_ENUM(NSUInteger, MDMFaceRegionType) {
    /** The region at the tip of the nose. */
    MDMFaceRegionTypeNose = 0,
    
    /** The region at the detected face's left side of the forehead. */
    MDMFaceRegionTypeForeheadLeft = 1,
    
    /** The region at the detected face's right side of the forehead. */
    MDMFaceRegionTypeForeheadRight = 2,
};

/**
 * Object that holds face mesh and transform data for detected face.
 */
@interface MDMFaceFrame : NSObject

- (instancetype)initWithData:(id)faceData;

@property (nonatomic, readonly) BOOL faceTracked;

@property(nonatomic, readonly) CVPixelBufferRef textureBuffer;

/**
 * The transform from camera to the center of the face, defined to have the origin located behind
 * the nose and between the two cheek bones. +Z is forward out of the nose, +Y is upwards, and +X is
 * towards the face's left. The units are in meters.
 */
@property(nonatomic, readonly) simd_float4x4 centerTransform;

/**
 * Transform from camera to to specified MDMFaceRegionType region
 */
- (simd_float4x4)transformForRegion:(MDMFaceRegionType)regionType;

/**
 * A 3D projection matrix that will result in the correct alignment of AR rendered content on top
 * of the captured camera image.
 *
 * @param viewPortSize The size of the view into which the AR content will be rendered.
 * @param presentationOrientation The orientation in which to display the AR content.
 *  UIDeviceOrientationUnknown, UIDeviceOrientationFaceUp and UIDeviceOrientationFaceDown map to
 *  UIDeviceOrientationPortrait.
 * @param mirrored Whether to provide a mirrored projection matrix. This will require you to flip
 *  the winding order for rendering.
 * @param zNear The near clipping distance in meters.
 * @param zFar The far clipping distance in meters. Must be positive and greater than the near
 *  distance.
 *
 * @remarks This method assumes camera images are rendered to aspect fill, not aspect fit.
 */
- (simd_float4x4)projectionMatrixForViewportSize:(CGSize)viewPortSize
                         presentationOrientation:(UIDeviceOrientation)presentationOrientation
                                        mirrored:(BOOL)mirrored
                                           zNear:(CGFloat)zNear
                                            zFar:(CGFloat)zFar;


/**
 * Number of vertices in the Augmented Faces mesh.
 *
 * The #vertexCount will not change.
 * Currently, there are 468 vertices, although this might change in the future.
 */
@property(nonatomic, readonly) NSUInteger vertexCount;

/**
 * A float buffer of 3D vertex locations in (x, y, z) packing.
 *
 * These vertices are relative to the center transform of the face. Units are in meters.
 */
@property(nonatomic, readonly) const simd_float3 *vertices;

/**
 * A float buffer of UV texture coordinates in (u, v) packing.
 *
 * There is a pair of texture coordinates for each vertex.
 * The textureCoordinates will not change.
 */
@property(nonatomic, readonly) const simd_float2 *textureCoordinates;

/**
 * A buffer of 3D normals in (x, y, z) packing.
 *
 * Each (x, y, z) is a unit vector of the normal to the surface at each vertex. There is
 * exactly one normal vector for each vertex. These normals are relative to center transform of
 * the face.
 */
@property(nonatomic, readonly) const simd_float3 *normals;

/**
 * Number of triangles in the face mesh.
 *
 * This is equivalent to the number of elements in #triangleIndices divided by 3.
 * The count will not change.
 */
@property(nonatomic, readonly) NSUInteger triangleCount;

/**
 * A buffer of triangles' indices in consecutive (i0, i1, i2) triplets.
 *
 * Every three consecutive values are indices that represent a triangle. The front face of each
 * triangle is defined by the face where the vertices are in counter clockwise winding order.
 *
 * The triangleIndices will not change.
 */
@property(nonatomic, readonly) const uint16_t *triangleIndices;


@end

NS_ASSUME_NONNULL_END
