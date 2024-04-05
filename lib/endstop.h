#ifndef ENDSTOP_H_
#define ENDSTOP_H_

class endstop {
public:

    endstop(uint8_t pin, bool default_state) {
        _pin = pin;
        _default_state = default_state;
    }

    // no boards with hardware pullups so far...
    void init() {
        pinMode(_pin, INPUT_PULLUP);  
    }

    // Read pin state and return
    bool get_state() {
        if (digitalRead(_pin) == _default_state)
            return true;
        else
            return false;
    }

private:
    uint8_t _pin;
    bool _default_state;
};

#endif /* ENDSTOP_H_ */
