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
int bVal = 0;


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
  // set the R, G, B value to output pins
  analogWrite(rPin, redValue);
  analogWrite(gPin, greenValue);
  analogWrite(bPin, blueValue);

  // set the global variable r, g, b values
  rVal = redValue;
  gVal = greenValue;
  bVal = blueValue;

  // print the current colour values
  Serial.print(rVal);
  Serial.print("\t");
  Serial.print(gVal);
  Serial.print("\t");
  Serial.println(bVal);
}

// === begin main loop
void loop() {

  if (irSignal.decode(&results)) {
    Serial.println(results.value);

    switch (results.value) {
      case 16718565:
        // solid red
        Serial.println("DETECT:\tRED");
        setRGB(255,0,0);
        break;
      case 16751205:
        // solid green
        Serial.println("DETECT:\tGREEN");
        setRGB(0,255,0);
        break;
    }
    
    irSignal.resume(); // Receive the next value
  }
}




/* DATASHEETS & AUXILLIARY INFORMATION

    DFRobot RGB LED Strip Driver Shield v1.0
    https://wiki.dfrobot.com/RGB_LED_Strip_Driver_Shield_SKU_DFR0274
    Inputs: 4: IR signal
    Outputs: 9, 10, 11 (PWM): RGB levels
    Additional 12V power in required

    Duoinotech RGB LED Module
    https://www.jaycar.com.au/medias/sys_master/images/images/9426937643038/XC4428-dataSheetMain.pdf
    https://arduinomodules.info/ky-009-rgb-full-color-led-smd-module/
    Note: Pins are labelled incorrectly on PCB - correct order is GROUND, GREEN, RED, BLUE
    
*/
