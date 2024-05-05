# Wire Wiggler Reference Hardware Design

This basic reference design is provided as is to those who wish to use it for a Wire Wiggler build. This prototype design should generally be limited to portable or otherwise non-permanent installs, where it is generally stored indoors and not exposed to harsh weather. The parts in BOM were chosen for common available from online vendors. There is a list of STL files that must be 3d printed to build the prototype, as well as STL files that can be used to construct the  8" cube box. 

Note the reference design makes use of affordable and readily available 3/4" EMT tubing for the shafts. However all parts except the printed 72T pulley are meant for 1" tubing. Therefore 1" tubing can also be used (author will upload model for 72T 1" pulleys soon). If 3/4 EMT is used, there are some shims to print that will keep the EMT adequately concentric on the bearings, clamps, etc.

Last but not least, there are many ways to construct a stepper motor antenna rotator for Wire Wiggler firmware. Any of the bits and pieces may be improvised as you see fit; hopefully with many parts you may already have on hand to keep the budget down (~$270 plus filament and time). Prices are from vendors that had parts available at the time of writing this page. 

## BOM
|	NOTE | QTY | DESCRIPTION | COST |  VENDOR  URL  |  VENDOR  QTY  |  VENDOR  PRICE	|
|  :---:    |        ---: |        :--- |        ---: |        :---    |        ---: |        ---:       	|
|   * | 1 |      Arduino  Nano  ATmega328p    | $7.99 |        [Amazon](https://www.amazon.com/OSOYOO-Arduino-Compatible-ATmega328p-Interface/dp/B0BCNCD1QT/)   | 1 | $7.99	|
|   * | 1 |      CNC  Shield  V4  Board      | $6.99 |        [Amazon](https://www.amazon.com/gp/product/B0BYMX542S/)      | 1 | $6.99	|
|   * | 1 |      Pi  Zero  2W | $20.79 |        [Amazon](https://www.amazon.com/Raspberry-Quad-core-Bluetooth-onboard-Antenna/dp/B0CCRP85TR/)      | 1 | $20.79	|
|   * | 1 |      5V  3A  Switching  Regulator   | $1.00 |        [Amazon](https://www.amazon.com/Regulator-Voltage-Adjustable-Converter-Transformer/dp/B08Y674Z6F/)   | 10 | $9.99	|
|   * | 2 |      Nema17  2A  Stepper  Motor  w/  19:1  Planetary  Gears      | $80.86 |        [Amazon](https://www.amazon.com/gp/product/B00QEUFRXK/)      | 1 | $40.43	|
|   * | 3 |      Endstop  Switches  'Roller  Type' | $1.80 |        [Amazon](https://www.amazon.com/HiLetgo-KW12-3-Roller-Switch-Normally/dp/B07X142VGC/)      | 10 | $5.99	|
|   * | 1 |      Momentary  NO  16mm  Panel  Button | $0.45 |        [Amazon](https://www.amazon.com/Clyxgs-Button-Switch-Momentary-20-Pack/dp/B07L1L5MZ3/)   | 20 | $8.99	|
|   * | 1 |      SPST  12mm  Waterproof  Panel  Switch   | $1.98 |        [Amazon](https://www.amazon.com/Nilight-Rocker-Toggle-Switch-Waterproof/dp/B078KBC5VH/)      | 5 | $9.89	|
|   * | 23 |      JST-XH  pin  connectors  [2,  3,  and  4pin] | $0.45 |        [Amazon](https://www.amazon.com/KSOPUERT-460PCS-Connector-Housing-Connectors/dp/B0CN6PWXR4/)    | 460 | $8.99	|
|   * | 2 |      Pillow  Block  'Flat  4-hole'  1"  UCF205-16      | $13.79 |        [Amazon](https://www.amazon.com/gp/product/B0C9LY2QQJ/) | 2 | $13.79	|
|   * | 2 |      Pillow  Block  'Flat  2-hole'  1"  UCFL205-16    | $15.99 |        [Amazon](https://www.amazon.com/dp/B09TS7FJGK/)      | 2 | $15.99	|
|   * | 2 |      Pulley  20T  GT2  6mm  Wide  8mm  Shaft   | $3.20 |        [Amazon](https://www.amazon.com/gp/product/B0CSMGSFPH/)      | 5 | $7.99	|
|   * | 3 |      GT2  120T  6mm  wide  timing  belt   | $3.18 |        [Amazon](https://www.amazon.com/gp/product/B0CMHVWTGF/)      | 10 | $10.59	|
|   * | 3 |      25mm  ID  45mm  OD  12mm  thick  Aluminum  Split  Shaft  Collar | $11.99 |        [Amazon](https://www.amazon.com/gp/product/B0BPCVN43N/)      | 4 | $15.99	|
|   * | 2 |      0.75"-1.25"  Motorcycle  Aluminum  Mounting  Bracket    | $7.93 |        [Amazon](https://www.amazon.com/gp/product/B0C6J48N1L/)      | 3 | $11.89	|
|   * | 8 |      1/2"-13  1.5"  Stainless  Steel  Hex  Bolts | $11.88 |        [Amazon](https://www.amazon.com/Available-Threaded-Stainless-Finish-Quantity/dp/B08JYLQJ7J/)   | 8 | $11.88	|
|   * | 8 |      1/2"-13  Stainless  Steel  Nut      | $6.39 |        [Amazon](https://www.amazon.com/Nuts-13-Stainless-Steel-10pcs/dp/B0BLBL8JS9/)      | 10 | $7.99	|
|   * | 16 |      1/2"  Stainless  Steel  Washer      | $5.75 |        [Amazon](https://www.amazon.com/Stainless-Outside-Diameter-Bolt-Dropper/dp/B073DKQKJD/)      | 25 | $8.99	|
|   * | 8 |      3/8"-16  1.5"  Stainless  Steel  Hex  Bolt   | $9.75 |        [Amazon](https://www.amazon.com/Available-Threaded-Stainless-Finish-Quantity/dp/B08G821T97/)   | 8 | $9.75	|
|   * | 8 |      3/8"-16  Stainless  Steel  Nut      | $4.79 |        [Amazon](https://www.amazon.com/Hillman-2532-8-16-Inch-Stainless-10-Pack/dp/B00HYLZ5VM/)   | 10 | $5.99	|
|   * | 16 |      3/8"  Stainless  Steel  Washer      | $3.99 |        [Amazon](https://www.amazon.com/AMLOOPH-Stainless-13-16-20/dp/B0CKBW38X4/)   | 20 | $4.99	|
|   * | 8 |      8-32  1"  Stainless  Steel  Phillips  Head  Bolt | $1.00 |        [Amazon](https://www.amazon.com/Prime-Line-9003664-Machine-Phillips-Stainless/dp/B074ZMYKXB/)      | 25 | $3.14	|
|   * | 8 |      8-32  Stainless  Steel  Hex  Nut    | $0.53 |        [Amazon](https://www.amazon.com/Instockbolts-Nuts-Stainless-Steel-100pcs/dp/B09V55FY7G/)   | 100 | $6.59	|
|   * | 8 |      #8  Stainless  Steel  Washer   | $0.56 |        [Amazon](https://www.amazon.com/Stainless-Flat-Washer-100-Pack/dp/B07KCYNXJL/)   | 100 | $6.99	|
|   * | 10 |      #10  Stainless  Steel  Phillips  Self  Tapping  Screw      | $0.90 |        [Amazon](https://www.amazon.com/Stainless-Steel-Phillips-Screws-Tapping/dp/B08V18RM6K/)      | 100 | $8.98	|
|   * | 1 |      Gland  Nut  [PG11]    | $0.40 |        [Amazon](https://www.amazon.com/Waterproof-Adjustable-Connectors-Plastic-Protectors/dp/B085NVDC3K/)      | 20 | $7.99	|
|   *   |   5   |   Foot of 3/4" EMT Conduit    |   $5.00   |   [Home Depot](https://www.homedepot.com/p/3-4-in-x-10-ft-Electrical-Metallic-Tubing-EMT-Conduit-0550110000/202068040)    |   10  |   $9.98   |
|   ** | 1 |      Pulley  20T  GT2  6mm  Wide  6mm  Shaft   | $1.40 |        [Amazon](https://www.amazon.com/gp/product/B077GNZK3J/)      | 5 | $6.99	|
|   ** | 1 |      10k  Linear  Potentiometer    | $7.88 |        [Amazon](https://www.amazon.com/dp/B0B3126K2M/ref=sspa_dk_detail_1?psc=1&pd_rd_i=B0B3126K2M/)      | 2 | $15.75	|
|   ** | 2 |      Pillow  Block  'Vertical'  1"  UPC205   | $15.75 |        [Amazon](https://www.amazon.com/gp/product/B07MWGF35D/)      | 2 | $15.75	|
|   ** | 1 |      Nema17  2A  Stepper  Motor      | $13.99 |        [Amazon](https://www.amazon.com/STEPPERONLINE-Stepper-Bipolar-Connector-compatible/dp/B00PNEQKC0/)   | 1 | $13.99	|
|   *** | 1 |      2.4/5GHz  Wifi  Antenna  w/  Male  RP-SMA  to  UFL  Cable   | $4.50 |        [Amazon](https://www.amazon.com/Bingfu-Bulkhead-Wireless-Extender-Repeater/dp/B00VE1XH4A/)   | 2 | $8.99	|
|   *** | 1 |      UFL  SMD  connector   | $4.30 |        [Amazon](https://www.amazon.com/RedYutou-Solder-Socket-Coaxial-Connector/dp/B0B9YRK8KQ/)   | 2 | $8.59	|
```
Notes:
*   Required (most '3@' items are 2@ when polarizer is not used)
**  Polarizer option requirements
*** External wifi antenna option
```

## 3D Printed Parts
Parts for the prototype were printed in PETG with 0.3mm thick layers, and otherwise basic settings. ASA is preferrable for longterm outdoor exposure (not recommended anyways). No supports are required for any of the models.

|   Note    |   QTY |   DESCRIPTION (LINK)    |
|   :---:   |   :---:   |   :---    |
|   *   |   2   |   [Antenna Adapter (3/4" square)](/models/antAdapter.stl) |
|   *   |   2   |   [Azimuth & Elevation Endstop Cams](/models/aziEleEndstopCam.stl)    |
|   *   |   1   |   [Azimuth Endstop Switch Mount](/models/aziEndstopMountPrint.stl)   |
|   *   |   1   |   [Azimuth Motor Mount](/models/aziMountPrint.stl)   |
|   *   |   1   |   [Elevation Endstop Switch Mount](/models/eleEndstopMountPrint.stl)   |
|   *   |   1   |   [Elveation Motor Mount](/models/eleMountPrint.stl)   |
|   *   |   1   |   [Nano CNC v4 Mount](/models/nanoCNCv4Base.stl)   |
|   *   |   1   |   [Pi Zero Mount](/models/piZeroMount.stl)   |
|   *   |   2   |   [Azimuth and Elevation Endstop Cam Shim for Conduit](/models/shimEndstopCam.stl)   |
|   *   |   6   |   [Shim for 1" Pillow Blocks with 3/4" EMT](/models/shimPillowBlock.stl)   |
|   **   |   1   |   [Control Box Bottom](/models/controlBoxBottom.stl)   |
|   **   |   1   |   [Control Box Top](/models/controlBoxTop.stl)   |
|   **   |   1   |   [Polarizer Endstop Cam](/models/polEndstopCam.stl)   |
|   **   |   1   |   [Polarizer Mount Bottom](/models/polMountBottom.stl)   |
|   **   |   1   |   [Polarizer Mount Top](/models/polMountTop.stl)   |
|   ***   |   2-3   |   [72T Pulley for 3/4" Conduit](/models/pulley1inch72T.stl)   |
|   ***   |   2-3   |   [Shim for 1" clamps with 3/4" EMT](/models/shimPulleyClamp.stl)   |
|   ****   |   NA   |   [Pulley Clamp Drill Guide](/models/drillGuidePulleyClamp.stl)   |
|   ****   |   NA   |   [Elevator Endstop Mount Shim](/models/shimEleEndstopMount.stl)   |
```
Notes:
*       Required
**      Polarizer option requirements
***     Quantity varies depending on use of polarizer option
****    Optional items... drill guide helps drilling the clamps. Elevator endstop shim is typically not needed unless box is constructed out of spec (pillow blocks too far fram front face of box).
```
## Box
The prototype was constructed using glue and 15/32" thick plywood, which was cut on a home brew MPCNC Primo J. The following STL's can be used to reproduce the exact same box if you have access to some means of creating one with whatever NC machines you may have access to. The interior size is roughly 8"x8"x9", for those inspired to roll their own to fit the above list of printed parts.

[Box Top](/models/top.stl)

[Box Bottom](/models/Bottom.stl)

[Box Front](/models/Front.stl)

[Box Back](/models/Back.stl)

[Box Left](/models/Left.stl)

[Box Right](/models/Right.stl)

##  Assembly
...work in progress

## Gallery
[Link to Wire Wiggler Gallery](/models/gallery.md)