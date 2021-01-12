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
  //! \param[in] setid  set id
  //! \param[in] constraint_fn math function
  //! \param[in] dir Direction of constraint load
  //! \param[in] velocity Constraint  velocity
  VelocityConstraint(int setid, const std::shared_ptr<mpm::FunctionBase>& constraint_fn,
                     unsigned dir, double velocity)
      : setid_{setid},
       constraint_fn_{constraint_fn},
       dir_{dir},
       velocity_{velocity} {};

  // Set id
  int setid() const { return setid_; }

  // Direction
  unsigned dir() const { return dir_; }

  // Return velocity
  double velocity(double current_time) const {
    double scalar = (this->constraint_fn_ != nullptr)
                      ? (this->constraint_fn_)->value(current_time)
                      : 1.0;
    return velocity_* scalar;
  }

 private:
  // ID
  int setid_;
  // Math Function
  const std::shared_ptr<FunctionBase>& constraint_fn_;
  // Direction
  unsigned dir_;
  // Velocity
  double velocity_;
};
}  // namespace mpm
#endif  // MPM_VELOCITY_CONSTRAINT_H_
