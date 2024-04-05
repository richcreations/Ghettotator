
#include <../src/config.h>


#ifdef DEBUG
    bool debug = 1;
#endif

#ifdef UNO_CNC_SHIELD_V_3
    #include <../boards/unoCncV3.h>
#endif
#ifdef BRUSHES_N_POTS
    #include <../boards/brushesNpots.h>
#endif
#ifdef ANET_A8_ATMEGA1280_PRINTER_BOARD
    #include <../boards/anet_a8_atmega1280.h>
#endif
#ifdef RAMPS_V_1_4_MEGA2560
    #include <../boards/ramps_V_1_4.h>
#endif