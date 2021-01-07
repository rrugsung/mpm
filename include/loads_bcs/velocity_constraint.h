#ifndef MPM_VELOCITY_CONSTRAINT_H_
#define MPM_VELOCITY_CONSTRAINT_H_

//! Alias for JSON
#include "json.hpp"
using Json = nlohmann::json;

#include "function_base.h"
namespace mpm {

//! VelocityConstraint class to store velocity constraint on a set
//! \brief VelocityConstraint class to store a constraint on a set
//! \details VelocityConstraint stores the constraint as a static value
class VelocityConstraint {
 public:
  // Constructor
  //! \param[in] set_id set id
  //! \param[in] constraint_fn math function
  //! \param[in] start_time start time
  //! \param[in] end_time end time
  //! \param[in] dir Direction of constraint load
  //! \param[in] velocity Constraint  velocity
  VelocityConstraint(int set_id, const std::shared_ptr<FunctionBase>& constraint_fn,
                     double start_time, double end_time, unsigned dir, double velocity)
      : set_id_{set_id},
      constraint_fn_{constraint_fn},
      start_time_{start_time},
      end_time_{end_time},
      dir_{dir}, 
      velocity_{velocity} {};

  // Set id
  int set_id() const {return set_id_; }
  // Start time
  double start_time() const { return start_time_; }
  
  // Start time
  double end_time() const { return end_time_; }
  
  // Direction
  unsigned dir() const { return dir_; }

  // Return velocity
  double velocity(double current_time) const {
    // Static load when no math function is defined
    double scalar = (this->constraint_fn_ != nullptr)
                        ? (this->constraint_fn_)->value(current_time)
                        : 1.0;
    return velocity_ * scalar;
  }
 private:
  // Set id
  int set_id_;
  // Math Function
  const std::shared_ptr<FunctionBase>& constraint_fn_;
  // Start Time
  double start_time_;
  // End Time
  double end_time_;
  // Direction
  unsigned dir_;
  // Velocity
  double velocity_;
};
}  // namespace mpm
#endif  // MPM_VELOCITY_CONSTRAINT_H_
