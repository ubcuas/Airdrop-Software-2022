#include "Operation.h"


/*
 * Purpose: calculate target reel down speed
 * Input: total distance to reel, current reeled distance
 * Output: target reeling speed
 */
double calcTargetSpeed(double total_dist, double dist_reeled) {
  double 
    decelerate_dist = 1 * 1.0, // Decelerates to a stop in this many meters
    max_speed = 1 * 0.20, // (m/s) 
    target_speed;
    
  if (dist_reeled < (total_dist - decelerate_dist)) {
    target_speed = max_speed;
  }
  else {
    target_speed = max_speed / decelerate_dist * (total_dist - dist_reeled); // linearly decrease to zero
  }

  return target_speed;
}