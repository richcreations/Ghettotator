/*!
*
*/

#ifdef UNO_CNC_SHIELD_V_3

    // Truglodite: rename to match CNC v3 shield https://osoyoo.com/wp-content/uploads/2017/04/Arduino-CNC-Shield-Scematics-V3.XX_.jpg
    #define xStep      2   // X step
    #define xDir       5   // X dir
    #define yStep      3   // Y Step
    #define yDir       6   // Y Dir
    #define EN         8   // Enable

    #define yEndstop   10  // Z endstop
    #define xEndstop   9   // X endstop

#endif // UNO_CNC_SHIELD_V_3