%
(Fusion CAM 2.0.18961)
( Posts processor: MPCNC21.cps)
( Gcode generated: Thursday, April 25, 2024 9:31:15 PM GMT)
( Document: wireWiggler v171)
( Setup: boxFront)
( )
( Ranges Table:)
(   X: Min=51.948 Max=194.958 Size=143.01)
(   Y: Min=102.524 Max=139.77 Size=37.246)
(   Z: Min=-13.392 Max=3 Size=16.392)
( )
( Tools Table:)
(  T1 D=3.175 CR=0 TAPER=118deg - ZMIN=-13.392 - drill )
( )
( Feedrate and Scaling Properties:)
(   Feed: Travel speed X/Y = 7500)
(   Feed: Travel Speed Z = 300)
(   Feed: Enforce Feedrate = true)
(   Feed: Scale Feedrate = false)
(   Feed: Max XY Cut Speed = 900)
(   Feed: Max Z Cut Speed = 180)
(   Feed: Max Toolpath Speed = 1000)
( )
( G1->G0 Mapping Properties:)
(   Map: First G1 -> G0 Rapid = true)
(   Map: G1s -> G0 Rapids = true)
(   Map: SafeZ Mode = Retract : default = 0)
(   Map: Allow Rapid Z = true)
( )
( *** START begin ***)
( --- Start custom gcode C:\Users\Kevin\Documents\Fusion 360\NC Programs\start.gcode)
% vfd enable
M6 T0
% LED ON
M62 P0
% spindle relays on
M62 P1
%( *** START end ***)
( )
( *** SECTION begin ***)
(   X Min: 142.247 - X Max: 194.958)
(   Y Min: 110.23 - Y Max: 139.77)
(   Z Min: -13.392 - Z Max: 3)
( SafeZ retract level not abs: 0)
( boxFrontDrill - Milling - Tool: 1 -  drill)
( COMMAND_START_SPINDLE)
( COMMAND_SPINDLE_CLOCKWISE)
( >>> Spindle Speed 5000)
M3 S5000
( COMMAND_COOLANT_ON)
( >>> WARNING: No matching Coolant channel : Flood requested)
G0 Z3 F300
X142.247 Y110.23 F7500
( MOVEMENT_CUTTING)
Z1 F300
G1 Z-3 F1000
G0 Z-2 F300
G1 Z-6 F1000
G0 Z-5 F300
G1 Z-9 F1000
G0 Z-8 F300
G1 Z-12 F1000
G0 Z3 F300
Z-10 F300
G1 Z-13.392 F1000
G0 Z3 F300
Y139.77 F7500
Z1 F300
G1 Z-3 F1000
G0 Z-2 F300
G1 Z-6 F1000
G0 Z-5 F300
G1 Z-9 F1000
G0 Z-8 F300
G1 Z-12 F1000
G0 Z3 F300
Z-10 F300
G1 Z-13.392 F1000
G0 Z3 F300
X194.958 F7500
Z1 F300
G1 Z-3 F1000
G0 Z-2 F300
G1 Z-6 F1000
G0 Z-5 F300
G1 Z-9 F1000
G0 Z-8 F300
G1 Z-12 F1000
G0 Z3 F300
Z-10 F300
G1 Z-13.392 F1000
G0 Z3 F300
Y110.23 F7500
Z1 F300
G1 Z-3 F1000
G0 Z-2 F300
G1 Z-6 F1000
G0 Z-5 F300
G1 Z-9 F1000
G0 Z-8 F300
G1 Z-12 F1000
G0 Z3 F300
Z-10 F300
G1 Z-13.392 F1000
G0 Z3 F300
( MOVEMENT_RAPID)
( *** SECTION end ***)
()
( *** SECTION begin ***)
(   X Min: 51.948 - X Max: 164.438)
(   Y Min: 102.524 - Y Max: 221.452)
(   Z Min: -2.954 - Z Max: 3)
( SafeZ retract level not abs: 0)
( boxFrontDrill 2 - Milling - Tool: 1 -  drill)
( COMMAND_START_SPINDLE)
( COMMAND_SPINDLE_CLOCKWISE)
( COMMAND_COOLANT_ON)
( >>> WARNING: No matching Coolant channel : Flood requested)
Z3 F300
X164.438 Y221.452 F7500
( MOVEMENT_CUTTING)
Z1 F300
G1 Z-2.954 F1000
G0 Z3 F300
Y177.472 F7500
Z1 F300
G1 Z-2.954 F1000
G0 Z3 F300
X80.94 Y102.524 F7500
Z1 F300
G1 Z-2.954 F1000
G0 Z3 F300
X51.948 F7500
Z1 F300
G1 Z-2.954 F1000
G0 Z3 F300
( MOVEMENT_RAPID)
( *** SECTION end ***)
()
( *** STOP begin ***)
( --- Start custom gcode C:\Users\Kevin\Documents\Fusion 360\NC Programs\end.gcode)
% spindle relays off
M63 P1
% LED Off
M63 P0
%%
