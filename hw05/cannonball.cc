#include <cstdio>
#include <cmath>
#include "functions.h"

int** cannonball(int** array, int scale) {
	int m = 80;				// mass of canonball in kg
	double t = 0.0;				// initial time
	double y = 0.0;				// vertical height above ground
	double x = 0.0;				// horizontal distance over ground
	int delta = 1000;			// initialize delta
//	int* delta = new int;
//	printf("Enter an angle of fire: ");	// prompt user for angle
//	scanf("%d", &delta);			// assign input to delta
	double vy = 250 * sin(delta);		// initial muzzle velocity of y in meters
	double vx = 250 * cos(delta);		// initial muzzle velicity of x in meters
	double v = 0.0;				// initial velocity
	double cD = 0.45;			// drag coefficient
	double aA = 0.03;			// area of object in square meters
	double dt = 1.0;			// change in time
	double g = 9.81;			// gravity acceleration in meters per second squared
	double p = 1.2;				// air density in kilograms per square meter
	double d;				// drag
	double ay;				// acceleration of vertical travel
	double ax;				// acceleration of horizontal travel
	delta = delta * M_PI / 180.0;		// converts delta to radians from degrees
	
	// loop until cannonball hits ground (y==0)
	while (y >= 0.0) {
		v = velocity(vy, vx);	// calculate velocity for drag
		d = drag(cD, aA, p, v, m);	// calculate drag
		ay = aOfY(g, d, vy, v);	// calculate ay
		ax = aOfX(d, vx, v);	// calculate ax
		vy = vOfN(vy, ay, dt);	// calculate velocity of y
		vx = vOfN(vx, ax, dt);	// calculate velocity of x
		y = dTravel(y, vy, dt);	// calculate change in height
		x = dTravel(x, vx, dt);	// calculate change in distance
		y = y/scale;		// divide current y by scale factor
		int iy = (int)y;	// cast y to int
		x = x/scale;		// divide current x by scale factor
		int ix = (int)x;	// cast x to int
		array[iy][ix] = '*';
		t += 1.0;	// increment time by 1 second
	}
	return array;
}