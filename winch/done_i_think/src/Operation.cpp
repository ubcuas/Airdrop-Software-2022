#include "Operation.h"


/*
 * Purpose: calculate target reel down speed
 * Input: total distance to reel, current reeled distance
 * Output: target reeling speed
 */
double calcTargetSpeed(double total_dist, double dist_reeled) {
  double 
    decelerate_dist = total_dist * 0.25, // Decelerates to a stop in this many meters *******************
    min_speed = 0.8, // (m/s) Slows to this speed when hits the ground *****************
    max_speed = 0.8, // (m/s) Max reeling down speed *******************
    target_speed;
    
  if (dist_reeled < (total_dist - decelerate_dist)) { // Has not reached deceleration point yet
    target_speed = max_speed;
  }
  else {
    // (max_speed - min_speed) is the part of the speed that linearly decreases to zero
    // min_speed is the contant speed that remains
    // (total_dist - dist_reeled) is the distance left until we hit the ground
    // decelerate_dist is as defined above
    
    double dist_left = total_dist - dist_reeled;
    if (dist_left < 0.0) // If negative, set to zero
      dist_left = 0.0;
    
    target_speed = (max_speed - min_speed) * (dist_left) / decelerate_dist + min_speed;
  }

  return target_speed;
}