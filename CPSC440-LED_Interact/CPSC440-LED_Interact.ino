/*
  State change detection (edge detection)

  Often, you don't need to know the state of a digital input all the time, but
  you just need to know when the input changes from one state to another.
  For example, you want to know when a button goes from OFF to ON. This is called
  state change detection, or edge detection.

  This example shows how to detect when a button or button changes from off to on
  and on to off.

  The circuit:
  - pushbutton attached to pin 2 from +5V
  - 10 kilohm resistor attached to pin 2 from ground
  - LED attached from pin 13 to ground (or use the built-in LED on most
    Arduino boards)

  created  27 Sep 2005
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ButtonStateChange
*/

// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int redLEDPin = 13;       // the pin that the LED is attached to
const int blueLEDPin = 12;
const int greenLEDPin = 8;

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);

  //cycle through all available colors
  //
}


void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // get the time in milli and use modulo of [random value ; like 12] to see if it equals 0
      // get random color function
      // timer set it to zero if color is green
            // if not, keep the timer going

  // keep color for so many cycles, then turn off rgb leds again
        // if its green, then call the playerLOSES function
      

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);

      // if green within a second, call the win function
      // if not green OR green but more than a second, call the lose function
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;


  

  // turns on the LED every four button pushes by checking the modulo of the
  // button push counter. the modulo function gives you the remainder of the
  // division of two numbers:
  if (buttonPushCounter % 4 == 0) {
    changeLED(true, true, true);        // white (all on)
  } else {
    changeLED(false, false, false);     // black (all off)
  }

}



void changeLED(bool red, bool blue, bool green) {
    int redState;
    int blueState;
    int greenState;
  
    if (red == true) redState == HIGH; else redState = LOW;
    if (blue == true) blueState == HIGH; else blueState = LOW;
    if (green == true) greenState == HIGH; else greenState = LOW;
    
    digitalWrite(redLEDPin, redState);
    digitalWrite(blueLEDPin, blueState);
    digitalWrite(greenLEDPin, greenState);
}


void randomColor() {
  // get a random value from 1 to 6

  // switch 1 to 6 case (red, green, blue, cyan, magenta, yellow)
  // green case, change the global variable for G_WINNING
}


void playerWINS() {
  // cycle through all the colors for x amount of seconds
}


void playerLOSES() {
  // flash red light for x amount of seconds
  // call the restart game function
}
