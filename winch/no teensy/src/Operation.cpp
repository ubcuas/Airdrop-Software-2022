#include "Operation.h"


/*
 * Purpose: calculate target reel down speed
 * Input: total distance to reel, current reeled distance
 * Output: target reeling speed
 */
double calcTargetSpeed(double total_dist, double dist_reeled) {
  double 
    decelerate_dist = total_dist * 0.25, // Decelerates to a stop in this many meters *******************
    max_speed = 0.2, // (m/s) *******************
    target_speed,
    extra = 0.4; // (m/s) ***************
    
  if (dist_reeled < (total_dist - decelerate_dist)) {
    target_speed = max_speed + extra;
  }
  else {
    target_speed = max_speed * (total_dist - dist_reeled) / decelerate_dist + extra ; // Linearly decrease to 0.05 *****************
  }

  return target_speed;
}