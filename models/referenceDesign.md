#Wire Wiggler Reference Hardware Design

##BOM

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