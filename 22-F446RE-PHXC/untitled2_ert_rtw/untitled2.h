//
// File: untitled2.h
//
// Code generated for Simulink model 'untitled2'.
//
// Model version                  : 1.36
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Tue Jan 19 01:11:37 2021
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_untitled2_h_
#define RTW_HEADER_untitled2_h_
#include "rtwtypes.h"
#include "untitled2_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

// Class declaration for model untitled2
class untitled2ModelClass {
  // public data and function members
 public:
  // Block states (default storage) for system '<Root>'
  typedef struct {
    real_T Delay_DSTATE[20];           // '<Root>/Delay'
    real_T UD_DSTATE;                  // '<S1>/UD'
    real_T Integrator_DSTATE;          // '<Root>/Integrator'
    real_T Integrator1_DSTATE;         // '<Root>/Integrator1'
  } DW_untitled2_T;

  // External inputs (root inport signals with default storage)
  typedef struct {
    real_T Target_Angle;               // '<Root>/Target_Angle'
    real_T Current_Angle;              // '<Root>/Current_Angle'
    real_T Kp;                         // '<Root>/Kp'
    real_T Ki;                         // '<Root>/Ki'
    real_T Kd;                         // '<Root>/Kd'
  } ExtU_untitled2_T;

  // External outputs (root outports fed by signals with default storage)
  typedef struct {
    real_T Stepper_Speed;              // '<Root>/Stepper_Speed'
  } ExtY_untitled2_T;

  // Real-time Model Data Structure
  struct RT_MODEL_untitled2_T {
    const char_T * volatile errorStatus;

    //
    //  Timing:
    //  The following substructure contains information regarding
    //  the timing information for the model.

    struct {
      struct {
        uint16_T TID[2];
      } TaskCounters;
    } Timing;
  };

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  void terminate();

  // Constructor
  untitled2ModelClass();

  // Destructor
  ~untitled2ModelClass();

  // Root-level structure-based inputs set method

  // Root inports set method
  void setExternalInputs(const ExtU_untitled2_T* pExtU_untitled2_T)
  {
    untitled2_U = *pExtU_untitled2_T;
  }

  // Root-level structure-based outputs get method

  // Root outports get method
  const untitled2ModelClass::ExtY_untitled2_T & getExternalOutputs() const
  {
    return untitled2_Y;
  }

  // Real-Time Model get method
  untitled2ModelClass::RT_MODEL_untitled2_T * getRTM();

  // private data and function members
 private:
  // Block states
  DW_untitled2_T untitled2_DW;

  // External inputs
  ExtU_untitled2_T untitled2_U;

  // External outputs
  ExtY_untitled2_T untitled2_Y;

  // Real-Time Model
  RT_MODEL_untitled2_T untitled2_M;
};

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'untitled2'
//  '<S1>'   : 'untitled2/Difference'

#endif                                 // RTW_HEADER_untitled2_h_

//
// File trailer for generated code.
//
// [EOF]
//
