// https://osoyoo.com/wp-content/uploads/2016/07/Schematic-2.png
// https://osoyoo.com/wp-content/uploads/2016/07/Schematic-1.png
#define aziStep      A0  // X step
#define aziDir       A1  // X direction
#define aziEN        38  // X enable
#define eleStep      A6  // Y step
#define eleDir       A7  // Y direction
#define eleEN        A2  // Y enable
#define polStep      46  // Z step
#define polDir       48  // Z direction
#define polEN        A8  // Z enable
#define tunStep      26  // E0 step
#define tunDir       28  // E0 direction
#define tunEN        24  // E0 enable
#define auxStep      36  // E1 step
#define auxDir       34  // E1 direction
#define auxEN        30  // E1 enable
// Code uses internal pullups
#define aziMinStop   3   // X- endstop
#define aziMaxStop   2   // X+ endstop
#define eleMinStop   14  // Y- endstop
#define eleMaxStop   15  // Y+ endstop
#define polMinStop   18  // Z- endstop
#define polMaxStop   19  // Z+ endstop

#define ledExists    1  // onboard led
#define ledPin       13  // onboard led