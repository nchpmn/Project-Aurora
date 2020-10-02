// === PROJECT AURORA ===
// --  RGB CONRTOLLER  --
// Info & Datasheets at bottom of code

// === import libraries
// IRremote - to read & decode IR signals
#include <IRremote.h>

// === declare global variables
// RGB Pins // These pins are correct - strips use the order "GRB"
int rPin = 10;
int gPin = 9;
int bPin = 11;

// IR receiver
int irPin = 4;
IRrecv irSignal(irPin);
decode_results results;

// RGB Values // Gotta store those colours somewhere!
int rVal = 0;
int gVal = 0;
int bVal = 128;

// Addition & Delay Variables // How big are the jumps?
int diffVal = 20;
int delayTime = 1000;


// === begin main setup
void setup() {
  // enable serial output
  // mostly for debugging - can be disabled in final product
  Serial.begin(9600);

  // set pin modes
  pinMode(rPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  Serial.println("RGB READY");

  // start IR 'listening'
  irSignal.enableIRIn();
  Serial.println("IR READY");
}

void setRGB(int redValue, int greenValue, int blueValue) {
  Serial.println("begin setRGB");
  // set the R, G, B value to output pins
  analogWrite(rPin, redValue);
  analogWrite(gPin, greenValue);
  analogWrite(bPin, blueValue);
  Serial.println("finish analogWrite");
  
  // set the global variable r, g, b values
  rVal = redValue;
  gVal = greenValue;
  bVal = blueValue;
  Serial.println("finish setting variables");
  
  // print the current colour values
  Serial.print(rVal);
  Serial.print("\t");
  Serial.print(gVal);
  Serial.print("\t");
  Serial.println(bVal);
  Serial.println("end setRGB");
  return;
}

// === begin main loop
void loop() {

  if (irSignal.decode(&results)) {
    Serial.println(results.value);

    switch (results.value) {
      // === solid colours - primary
      case 16718565:
        // solid red
        Serial.println("DETECT:\tRED");
        setRGB(255, 0, 0);
        break;
      case 16751205:
        // solid green
        Serial.println("DETECT:\tGREEN");
        setRGB(0, 255, 0);
        break;
      case 16753245:
        // solid green
        Serial.println("DETECT:\tBLUE");
        setRGB(0, 0, 255);
        break;
      case 16720605:
        // solid white
        Serial.println("DETECT:\tWHITE");
        setRGB(255, 255, 255);
        break;

      // === solid colours - secondary
      case 16734375:
        // solid purple 3
        Serial.println("DETECT:\tPURPLE 3");
        setRGB(255, 0, 255);
        break;

      // === add/minus colours
      case 16722135:
        // add red
        Serial.println("DETECT:\tADD RED");
        if (rVal + diffVal > 255) {
          setRGB(255, gVal, bVal);
        } else {
          setRGB(rVal + diffVal, gVal, bVal);
        }
        break;
      case 16713975:
        // minus red
        Serial.println("DETECT:\tMINUS RED");
        if (rVal - diffVal < 0) {
          setRGB(0, gVal, bVal);
        } else {
          setRGB(rVal - diffVal, gVal, bVal);
        }
        break;
      case 16771095:
        // add blue
        Serial.println("DETECT:\tADD BLUE");
        setRGB(rVal, gVal, 200);
        break;

      case 16754775:
        // add green
        Serial.println("DETECT:\tADD GREEN");
        if (gVal + diffVal > 255) {
          setRGB(rVal, 255, bVal);
        } else {
          setRGB(rVal, gVal + diffVal, bVal);
        }
        break;
      case 16746615:
        // minus green
        Serial.println("DETECT:\tMINUS GREEN");
        if (gVal - diffVal < 0) {
          setRGB(rVal, 0, bVal);
        } else {
          setRGB(rVal, gVal - diffVal, bVal);
        }
        break;
        

    }
    Serial.println("begin IR resume");
    irSignal.resume(); // Receive the next value
    Serial.println("end IR resume");
  }
}




/* DATASHEETS & AUXILIARY INFORMATION

    DFRobot RGB LED Strip Driver Shield v1.0
    https://wiki.dfrobot.com/RGB_LED_Strip_Driver_Shield_SKU_DFR0274
    Inputs: 4: IR signal
    Outputs: 9, 10, 11 (PWM): RGB levels
    Additional 12V power in required

    IR Remote Button Codes
    https://docs.google.com/spreadsheets/d/11EeZW00qZXZrF_tCHybD09vXJeLdS_K2JR_PmxucZL4/edit#gid=12233873

    Duoinotech RGB LED Module
    https://www.jaycar.com.au/medias/sys_master/images/images/9426937643038/XC4428-dataSheetMain.pdf
    https://arduinomodules.info/ky-009-rgb-full-color-led-smd-module/
    Note: Pins are labelled incorrectly on PCB - correct order is GROUND, GREEN, RED, BLUE

*/
