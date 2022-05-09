#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 100
// Define the array of leds
CRGB leds[NUM_LEDS];
#define DATA_PIN 3
#define LEDPIN 13   // remove


#define BUTTON_PIN 2    // the pin that the pushbutton is attached to

bool is_color = false;
bool is_green = false;
int greentimer = 0;
int hold_button_timer = 0;
int cur_color_timer = 10000;
int difficulty = 0;
const int darken = 125; // limit is 255


// Variables will change:
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button


void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  pinMode(BUTTON_PIN, INPUT);
  
  pinMode(LEDPIN, OUTPUT);    // remove
  digitalWrite(LEDPIN, LOW);  // remove
  
  delay(1000);                  // let the system start up
  //rainbowColor(5,5,0,255);   // startup animation
  allColor(255,255,255);
  delay(5000);
  allColor(0,0,0);

  Serial.begin(250000);
}


void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(BUTTON_PIN);
  delay(50);
    
  greentimer++;
  cur_color_timer++;

  if((cur_color_timer >= (60 - difficulty))) {   // 60 is 3 seconds?
    randomColor();
    cur_color_timer = 0;
  }

//  if(cur_color_timer >= 3000) {
//    if(true) { //random timing for new color
//      // ((random(10) % 2) == 0)
//      if(randomColor()) {
//        greentimer = 0;
//      }
//    } else {
//      allColor(0,0,0);
//    }
//  }

  // keep color for so many cycles, then turn off rgb leds again
        // if its green, then call the playerLOSES function
      

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      digitalWrite(LEDPIN, HIGH);   // remove
      // if the current state is HIGH then the button went from off to on:
      // check if current color is green and timer is under a second
      if((is_green == true) && (greentimer <= (40 - difficulty))) {
        Serial.println("Green was on and you pushed the button!");
        playerWINS();
        is_green = false;
        is_color = false; 
        cur_color_timer = 0;
        if (difficulty <= 35) {
          difficulty += 5;
        }
        allColor(0,0,0);
        Serial.print("Current difficulty: ");
        Serial.println(difficulty);
      } else {
        Serial.println("No green and you pushed the button!");
        playerLOSES();
      }
      // on

      // if green within a second, call the win function
      // if not green OR green but more than a second, call the lose function
    } else {
      // if the current state is LOW then the button went from on to off:
      // off
      digitalWrite(LEDPIN, LOW);    // remove
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;

  
  if ((greentimer >= (40 - difficulty)) && is_green == true) {
    Serial.println("Green was on, you lose!");
    playerLOSES();
  }

}



void allColor(int red, int green, int blue) {
  for(int i=0; i <= NUM_LEDS; i++) {
    leds[i] = CRGB(red,green,blue);
  }
  FastLED.show();
}


// fade time is in seconds
void fadeColor(int red, int green, int blue, float fade) {
    for(int i = 0; i <= NUM_LEDS ; i++) {
      leds[i] = CRGB(red, green, blue);
      FastLED.show();
      delay(fade * 1000);
      //Serial.print("currently on pixel: ");
      //Serial.println(i);
  }
}


bool randomColor() {
  // get a random value from 1 to 6
  int var = random(6) + 1;
  is_green =  false;
  is_color =  true;
  cur_color_timer = 0;

  // switch 1 to 6 case (red, green, blue, cyan, magenta, yellow)
  switch (var) {
    case 1:
      allColor(255 - darken, 0, 0);  // red
      Serial.println("its red");
      break;
    case 2:
      allColor(0, 0, 255 - darken);  // blue
      Serial.println("its blue");
      break;
    case 3:
      allColor(0, 255 - darken, 0);  // green
      greentimer = 0;
      is_green =  true;
      Serial.println("Its green!");
      break;
    case 4:
      allColor(0, 255 - darken, 255 - darken);     // cyan
      Serial.println("its cyan");
      break;
    case 5:
      allColor(255 - darken, 255 - darken, 0);     // yellow
      Serial.println("its yellow");
      break;
    case 6:
      allColor(255 - darken, 0, 255 - darken);   // magenta
      Serial.println("its magenta");
      break;
    default:
      allColor(0, 0, 0);   // off
      Serial.println("its off");
      is_color = false;
      break;
  }

  return is_color;
}


void playerWINS() {
  int waittime = 500;    // half of a second each color
  
  // cycle through all the colors for x amount of seconds
  allColor(255, 255, 255);    //white
  delay(waittime);
  allColor(255, 0, 255);   //yellow
  delay(waittime);
  allColor(255, 255, 0);   // magenta
  delay(waittime);
  allColor(0, 255, 255);   // cyan
  delay(waittime);
  allColor(0, 0, 255);  // green
  delay(waittime);
  allColor(0, 255, 0);  // blue
  delay(waittime);
  allColor(255, 0, 0);  // red
  delay(waittime);
  allColor(0,0,0);

  //start();
}

// how long for animation and cycles per second
// minVal is how dark it can ever get ; maxVal is how bright it can ever get
void rainbowColor(int seconds, int cycles, int minVal, int maxVal) {
  int intervals = (255/3);        // color bit depth / amount of colors on pixel(rgb)
  int red = intervals * 0;
  int rmul = 1;                   // swap between positive one and negative one
  int green = intervals * 1;
  int gmul = 1;                   // swap between positive one and negative one
  int blue = intervals * 2;
  int bmul = 1;                   // swap between positive one and negative one

  for (int j=0; j <= seconds*cycles; j++) {
    for (int i=0; i <= NUM_LEDS; i++) {
      if (red > maxVal || red < minVal) rmul *= -1;
      if (green > maxVal || green < minVal) gmul *= -1;
      if (blue > maxVal || blue < minVal) bmul *= -1;
      leds[i] = CRGB(red+rmul, green+gmul, blue+bmul);
    }
    FastLED.show();
    delay(1000 / cycles);
  }
  allColor(0,0,0);
}


void playerLOSES() {
  int waittime = 500;    // half of a second each color
  int amount = 3;       // amount of times blinking
  
  // flash red light for x amount of seconds
  for (int i = 0; i <= amount; i++) {
    allColor(255, 0, 0);  // red
    delay(waittime);
    allColor(0, 0, 0);  // off
    delay(waittime);
  }

  // call the restart game function
   start();
}



void start() {
  // reintialize the counters
  is_color = false;
  is_green = false;
  greentimer = 0;
  difficulty = 0;
  cur_color_timer = 0;
  allColor(0, 0, 0);
  buttonState = 0;         // current state of the button
  lastButtonState = 0;     // previous state of the button
  digitalWrite(LEDPIN, LOW);   // remove
  delay(500);
  
  // hold button for x amount of seconds to start game
  while(true) {
  // compare the buttonState to its previous state
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    while (digitalRead(BUTTON_PIN) == HIGH) {
      hold_button_timer++;
      if(hold_button_timer >= 3000) {
        rainbowColor(3,30,100,255);
        buttonState = 0;         // current state of the button
        lastButtonState = 0;     // previous state of the button
        hold_button_timer = 0;
        while (true) loop();
      }
      delay(1);
    }
    hold_button_timer = 0;
    digitalWrite(LEDPIN, LOW);   // remove
    buttonState = 0;         // current state of the button
    lastButtonState = 0;     // previous state of the button
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  }
}
