/*!
*
*/

#ifdef UNO_CNC_SHIELD_V_3

    // Truglodite: rename to match CNC v3 shield https://osoyoo.com/wp-content/uploads/2017/04/Arduino-CNC-Shield-Scematics-V3.XX_.jpg
    #define aziStep      2   // X step
    #define aziDir       5   // X dir
    #define eleStep      3   // Y Step
    #define eleDir       6   // Y Dir
    #define polStep      4   // Z Step
    #define polDir       7   // Z Dir
    #define tunStep      12  // A Step (open spindle en jumper)
    #define tunDir       13  // A Dir (open spindle dir jumper)
    #define aziMinStop   8   // All Steppers Enable
    // Shield has no built in pullups
    #define aziMinStop   9   // X endstop
    #define eleMinStop   10  // Y endstop
    #define eleMinStop   11  // Z endstop

#endif // UNO_CNC_SHIELD_V_3