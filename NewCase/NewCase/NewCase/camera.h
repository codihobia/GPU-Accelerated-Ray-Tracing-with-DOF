#pragma once
#include <cuda_runtime.h>
#include <vector_types.h>
#include<oidn.hpp>
#include "device_launch_parameters.h"
#include "helperMath.h"
struct Ray {
	float3 orig; // ray origin
	float3 dir;  // ray direction 
	__device__ Ray(float3 o_, float3 d_) : orig(o_), dir(d_) {}
};




struct Camera
{

	Camera(float3 lookfrom, float3 lookat, float3 vup, float vfov, float aspect, float aparture, float focus_dist)
	{
		lens_radius = aparture / 2;
		float theta = float(vfov * M_PI / 180);
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		origin = lookfrom;
		w = normalize(lookfrom - lookat);
		u = normalize(cross(vup,w));
		v = cross(w, u);
		lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
		horizontal = 2 * half_width * focus_dist * u;
		vertical = 2 * half_height * focus_dist * v;

	}
	
	float3 origin;
	float3 lower_left_corner;
	float3 horizontal;
	float3 vertical;
	float3 u, v, w;
	float lens_radius;



};