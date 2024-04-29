%
(Fusion CAM 2.0.18961)
( Posts processor: MPCNC21.cps)
( Gcode generated: Friday, April 26, 2024 5:50:58 PM GMT)
( Document: wireWiggler v176)
( Setup: boxDoor)
( )
( Ranges Table:)
(   X: Min=11.35 Max=145.87 Size=134.52)
(   Y: Min=11.35 Max=177.178 Size=165.828)
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
(   X Min: 11.35 - X Max: 145.87)
(   Y Min: 11.35 - Y Max: 177.178)
(   Z Min: -13.392 - Z Max: 3)
( SafeZ retract level: 3)
( boxDoorDrill - Milling - Tool: 1 -  drill)
( COMMAND_START_SPINDLE)
( COMMAND_SPINDLE_CLOCKWISE)
( >>> Spindle Speed 5000)
M3 S5000
( COMMAND_COOLANT_ON)
( >>> WARNING: No matching Coolant channel : Flood requested)
G0 Z3 F300
X39.35 Y11.35 F7500
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
X11.35 Y39.35 F7500
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
Y94.264 F7500
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
Y149.178 F7500
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
X39.35 Y177.178 F7500
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
X117.87 F7500
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
X145.87 Y149.178 F7500
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
Y94.264 F7500
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
Y39.35 F7500
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
X117.87 Y11.35 F7500
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
( *** STOP begin ***)
( --- Start custom gcode C:\Users\Kevin\Documents\Fusion 360\NC Programs\end.gcode)
% spindle relays off
M63 P1
% LED Off
M63 P0
%%
