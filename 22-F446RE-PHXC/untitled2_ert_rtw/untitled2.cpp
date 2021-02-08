//
// File: untitled2.cpp
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
#include "untitled2.h"
#include "untitled2_private.h"

static void rate_scheduler(untitled2ModelClass::RT_MODEL_untitled2_T *const
  untitled2_M);

//
//   This function updates active task flag for each subrate.
// The function is called at model base rate, hence the
// generated code self-manages all its subrates.
//
static void rate_scheduler(untitled2ModelClass::RT_MODEL_untitled2_T *const
  untitled2_M)
{
  // Compute which subrates run during the next base time step.  Subrates
  //  are an integer multiple of the base rate counter.  Therefore, the subtask
  //  counter is reset when it reaches its limit (zero means run).

  (untitled2_M->Timing.TaskCounters.TID[1])++;
  if ((untitled2_M->Timing.TaskCounters.TID[1]) > 999) {// Sample time: [1.0s, 0.0s] 
    untitled2_M->Timing.TaskCounters.TID[1] = 0;
  }
}

// Model step function
void untitled2ModelClass::step()
{
  int_T idxDelay;
  real_T rtb_Error;
  real_T rtb_Add;
  real_T rtb_Delay;
  real_T rtb_Switch1;
  real_T rtb_Add_0;
  if ((&untitled2_M)->Timing.TaskCounters.TID[1] == 0) {
    // Delay: '<Root>/Delay'
    rtb_Delay = untitled2_DW.Delay_DSTATE[0];

    // Sum: '<Root>/Error' incorporates:
    //   Inport: '<Root>/Current_Angle'
    //   Inport: '<Root>/Target_Angle'

    rtb_Error = untitled2_U.Current_Angle - untitled2_U.Target_Angle;

    // Sum: '<Root>/Add' incorporates:
    //   DiscreteIntegrator: '<Root>/Integrator'
    //   DiscreteIntegrator: '<Root>/Integrator1'
    //   Inport: '<Root>/Kd'
    //   Inport: '<Root>/Ki'
    //   Inport: '<Root>/Kp'
    //   Product: '<Root>/Product'
    //   Product: '<Root>/Product1'
    //   Product: '<Root>/Product2'
    //   Sum: '<Root>/Subtract'
    //   Sum: '<S1>/Diff'
    //   UnitDelay: '<S1>/UD'
    //
    //  Block description for '<S1>/Diff':
    //
    //   Add in CPU
    //
    //  Block description for '<S1>/UD':
    //
    //   Store in Global RAM

    rtb_Add = ((rtb_Error - untitled2_DW.UD_DSTATE) * untitled2_U.Kd +
               untitled2_U.Kp * rtb_Error) + (untitled2_DW.Integrator_DSTATE -
      untitled2_DW.Integrator1_DSTATE) * untitled2_U.Ki;

    // Signum: '<Root>/Sign'
    if (rtb_Error < 0.0) {
      rtb_Switch1 = -1.0;
    } else if (rtb_Error > 0.0) {
      rtb_Switch1 = 1.0;
    } else if (rtb_Error == 0.0) {
      rtb_Switch1 = 0.0;
    } else {
      rtb_Switch1 = (rtNaN);
    }

    // End of Signum: '<Root>/Sign'

    // Signum: '<Root>/Sign1'
    if (rtb_Add < 0.0) {
      rtb_Add_0 = -1.0;
    } else if (rtb_Add > 0.0) {
      rtb_Add_0 = 1.0;
    } else if (rtb_Add == 0.0) {
      rtb_Add_0 = 0.0;
    } else {
      rtb_Add_0 = (rtNaN);
    }

    // End of Signum: '<Root>/Sign1'

    // Switch: '<Root>/Switch1' incorporates:
    //   Constant: '<Root>/Constant2'
    //   Logic: '<Root>/Logical Operator'
    //   RelationalOperator: '<Root>/Equal'
    //   RelationalOperator: '<Root>/NotEqual'

    if ((rtb_Switch1 == rtb_Add_0) && (rtb_Add != rtb_Add)) {
      rtb_Switch1 = rtb_Error;
    } else {
      rtb_Switch1 = 0.0;
    }

    // End of Switch: '<Root>/Switch1'

    // Sum: '<Root>/Add1' incorporates:
    //   Delay: '<Root>/Delay1'

    untitled2_Y.Stepper_Speed += rtb_Add;

    // Update for Delay: '<Root>/Delay'
    for (idxDelay = 0; idxDelay < 19; idxDelay++) {
      untitled2_DW.Delay_DSTATE[idxDelay] = untitled2_DW.Delay_DSTATE[idxDelay +
        1];
    }

    untitled2_DW.Delay_DSTATE[19] = rtb_Switch1;

    // End of Update for Delay: '<Root>/Delay'

    // Update for UnitDelay: '<S1>/UD'
    //
    //  Block description for '<S1>/UD':
    //
    //   Store in Global RAM

    untitled2_DW.UD_DSTATE = rtb_Error;

    // Update for DiscreteIntegrator: '<Root>/Integrator'
    untitled2_DW.Integrator_DSTATE += rtb_Switch1;

    // Update for DiscreteIntegrator: '<Root>/Integrator1'
    untitled2_DW.Integrator1_DSTATE += rtb_Delay;
  }

  rate_scheduler((&untitled2_M));
}

// Model initialize function
void untitled2ModelClass::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
}

// Model terminate function
void untitled2ModelClass::terminate()
{
  // (no terminate code required)
}

// Constructor
untitled2ModelClass::untitled2ModelClass():
  untitled2_DW()
  ,untitled2_U()
  ,untitled2_Y()
  ,untitled2_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
untitled2ModelClass::~untitled2ModelClass()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
untitled2ModelClass::RT_MODEL_untitled2_T * untitled2ModelClass::getRTM()
{
  return (&untitled2_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
