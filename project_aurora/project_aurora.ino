// === PROJECT AURORA ===
// --  RGB CONRTOLLER  --
// Info & Datasheets at bottom of code

// declare global variables
int ledR = 10;
int ledG = 9; // yes, these pins are correct
int ledB = 11;


void setup() {
  // set pin modes
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);


}

void loop() {
  
}

/* DATASHEETS & AUXILLIARY INFORMATION
 *  
 *  DFRobot RGB LED Strip Driver Shield v1.0
 *  https://wiki.dfrobot.com/RGB_LED_Strip_Driver_Shield_SKU_DFR0274
 *  Inputs: 4: IR signal
 *  Outputs: 9, 10, 11 (PWM): RGB levels
 *  Additional 12V power in required
 *  
 *  Duoinotech RGB LED Module
 *  https://www.jaycar.com.au/medias/sys_master/images/images/9426937643038/XC4428-dataSheetMain.pdf
 *  https://arduinomodules.info/ky-009-rgb-full-color-led-smd-module/
 *  Note: Pins are labelled incorrectly on PCB - correct order is GROUND, GREEN, RED, BLUE
 */
