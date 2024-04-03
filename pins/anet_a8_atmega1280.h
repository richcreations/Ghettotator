#ifdef ANET_A8_ATMEGA1280_PRINTER_BOARD

    // Truglodite: rename to match anet a8 mainboard https://kingshobbiesbrasil.wixsite.com/p3dp/f-rum/projetos-dicas/esquema-eletronico-da-placa-anet-a8
    #define aziStep      16  // X step
    #define aziDir       24  // X dir
    #define eleStep      25  // Y Step
    #define eleDir       26  // Y Dir
    #define polStep      43  // Z Step
    #define polDir       42  // Z Dir
    #define tunStep      41  // E Step
    #define tunDir       40  // E Dir
    #define aziMinStop         15  // Enable Steppers
    // Shield has no built in pullups
    #define aziMinStop   21  // X endstop
    #define eleMinStop   22  // Y endstop
    #define polMinStop   23  // Z endstop

#endif // ANET_A8_ATMEGA1280_PRINTER_BOARD