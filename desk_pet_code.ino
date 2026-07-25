#include <DIYables_LCD_I2C.h>

const int FEED_BUTTON_PIN = 13;
const int PET_BUTTON_PIN = 12;

byte backslash[8] = {
  0b00000,
  0b10000,
  0b01000,
  0b00100,
  0b00010,
  0b00001,
  0b00000,
  0b00000
};

String name = "Nano";
double foodLevel = 8.0;
double affectionLevel = 8.0;
   
void decreaseHunger() {
  if (foodLevel - 0.2 < 0) {
    foodLevel = 0;
  } else {
    foodLevel -= 0.2;
  }
}

void decreaseAffection() {
  double affectionDecrease = ((1/affectionLevel));
  if (affectionLevel - affectionDecrease < 0) {
    affectionLevel = 0;
  } else {
    affectionLevel -= affectionDecrease;
  }
}

void increaseFoodLevel() {
  if (foodLevel + 1 <= 10) {
    foodLevel += 1;
  }
}

void increaseAffectionLevel() {
  if (affectionLevel + 1 <= 10) {
    affectionLevel += 1;
  }
  
}

void setName(String petName) {
  name = petName;
}

String getMood() {
  String mood = "happy";
  
  if (foodLevel < 3 && affectionLevel < 3) {
    mood = "miserable";

  } else if (foodLevel < 3 && affectionLevel >= 3) {
      mood = "angry";

  } else if (foodLevel >= 3 && affectionLevel < 3) {
      mood = "sad";

  } else if (foodLevel < 7 || affectionLevel < 7) {
      mood = "annoyed";

  } else {
      mood = "happy";
  }
  
  return mood;

  }
  

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
  
const int RED_PIN = 4, GREEN_PIN = 3, BLUE_PIN = 2;

void setMoodLightRGBColor(int r, int g, int b) {
  
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);
}

void turnOffMoodLight() {
  analogWrite(RED_PIN, 0);
  analogWrite(GREEN_PIN, 0);
  analogWrite(BLUE_PIN, 0);
}

void setMoodColor() {
  
  String mood = getMood();
  
  // purple for depressed
  int r = 19, g = 38, b = 92;
  
  if (mood == "happy") {
     // yellow
     r = 255, g = 255, b = 0;
   } else if (mood == "neutral") {
     // white
     r = 255, g = 255, b = 255;
   } else if (mood == "annoyed") {
     // orange
     r = 220, g = 77, b = 1;
   } else if (mood == "angry") {
     // red
     r = 255, g = 0, b = 0;
   } else if (mood == "sad") {
    // blue
     r = 0, g = 0, b = 255;
   }
  
  setMoodLightRGBColor(r, g, b);
}

const int ACTION_BUTTON = 7;

DIYables_LCD_I2C lcd(0x27,  16, 2);

void updateFace() {
  
  const String mood = getMood();
  
  setExpression(mood);
  
}

void setExpression(String mood) {

  String eyeType = "";
  String mouthType = "upset";
  
  if (mood == "happy") {
    eyeType = "happy";
    mouthType = "happy";
  } else if (mood == "neutral") {
    eyeType = "neutral";
    mouthType = "neutral";
  } else if (mood == "annoyed") {
    eyeType = "annoyed";
    mouthType = "annoyed";
  } else if (mood == "miserable") {
    eyeType = "miserable";
  } else if (mood == "sad") {
    eyeType = "sad";
  } else if (mood == "angry") {
    eyeType = "angry";
  } 
  
  setEyes(eyeType);
  setMouth(mouthType);
}

void setMouth(String mouthType) {
  lcd.setCursor(0, 1);

  if (mouthType == "upset") {
    lcd.print("       /");
    lcd.write(0);
    lcd.print("       ");
  } else if (mouthType == "neutral") {
    lcd.print("       vv       ");
  } else if (mouthType == "annoyed") {
    lcd.print("      ----      ");
  } else if (mouthType == "happy") {
    lcd.print("       ");
    lcd.write(0);
    lcd.print("/       ");
  }
}

void setEyes(String eyeType) {
  lcd.setCursor(0, 0);

  if (eyeType == "angry") {
    lcd.print("    o");
    lcd.write(0);
    lcd.write(0);
    lcd.print("__//o  + ");
  } else if (eyeType == "neutral") {
    lcd.print("   o        o   ");
  } else if (eyeType == "annoyed") {
    lcd.print("   o");
    lcd.write(0);
    lcd.print("      /o + ");
  } else if (eyeType == "miserable") {
    lcd.print("   /O **** O");
    lcd.write(0);
    lcd.print("   ");
  } else if (eyeType == "sad") {
    lcd.print("   /o      o");
    lcd.write(0);
    lcd.print("   ");
  } else if (eyeType == "happy") {
    lcd.print("   _O      O_   ");
  } else if (eyeType == "action") {
    lcd.print("    n      n    ");
  }
  
}

void blink() {
  lcd.setCursor(3, 0);
  lcd.print("__");
  lcd.setCursor(11, 0);
  lcd.print("__");
}

void clearFace() {
  lcd.clear();
}

void showIsEating() {
  lcd.clear();
  
  if (name.length() <= 7) {
    lcd.print(name + " is still");
    lcd.setCursor(0, 1);
    lcd.print("eating!");
  } else if (name.length() < 13) {
    lcd.print(name + " is");
    lcd.setCursor(0, 1);
    lcd.print("still eating!");
  } else {
    lcd.print(name);
    lcd.setCursor(0, 1);
    lcd.print("is still eating!");
  }
  
}

void showDoesNotWantsPets() {
  lcd.clear();
  
  if (name.length() <= 2) {
    lcd.print(name + " does not want");
    lcd.setCursor(0, 1);
    lcd.print("pets");
  } else if (name.length() <= 7) {
    lcd.print(name + " does not");
    lcd.setCursor(0, 1);
    lcd.print("want pets");
  } else if (name.length() <= 11) {
    lcd.print(name + " does");
    lcd.setCursor(0, 1);
    lcd.print("not want pets");
  } else {
    lcd.print(name);
    lcd.setCursor(0, 1);
    lcd.print("does not want pets");
  }
    
}

unsigned long timeFed = 0;

boolean canEat() {
  if (((millis() - timeFed) > 5000) || timeFed == 0) {
  	return true;
  }
  return false;
}

unsigned long timePet = 0;

boolean wantsPets() {
  if (((millis() - timePet) > 5000) || timePet == 0) {
  	return true;
  }
  return false;
}

void setup() {
  
  Serial.begin(9600); // Initialize communication at 9600 bits per second

  
  
  //initialize lcd screen
  lcd.init();

  lcd.createChar(0, backslash);
  
  // turn on the backlight
  lcd.backlight();
  
  // hide cursor
  
  lcd.noCursor();
  lcd.noBlink();
  
  // setup push buttons
  
  pinMode(FEED_BUTTON_PIN, INPUT_PULLUP);
  pinMode(PET_BUTTON_PIN, INPUT_PULLUP);
  
  // setup pins for RGB LED control
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  lcd.setCursor(0, 0);
  updateFace();
  
}
  
boolean moodLightOn = false;
boolean backLightOn = true;
unsigned long lightOnStart = 0;
unsigned long timeBlinkStart = 0;
unsigned long timeTextStart = 0;
unsigned long timeHungerDecrease = 0;
unsigned long timeAffectionDecrease = 0;

String state = "mood";


void loop() {
    // read the state of the pushbutton value:
    int feedButtonState = digitalRead(FEED_BUTTON_PIN);
    int petButtonState = digitalRead(PET_BUTTON_PIN);

    static int lastFeedState = 1;
    static int lastPetState = 1;

    if (moodLightOn && (millis() - lightOnStart > 500)) {
        moodLightOn = false;
        turnOffMoodLight();
    }

    if (millis() - timeHungerDecrease > 10000) {
      decreaseHunger();
      Serial.println(foodLevel);
      timeHungerDecrease = millis();
      if (state == "mood") {
          updateFace();
      }
    }

    if (millis() - timeAffectionDecrease > 10000) {
      decreaseAffection();
      Serial.println("affectionLevel");
      Serial.println(affectionLevel);
      timeAffectionDecrease = millis();
      if (state == "mood") {
          updateFace();
      }
    }

    if (millis() - timeBlinkStart > 5000 && state != "action") {
        state = "blink";
        blink();
        timeBlinkStart = millis();
    }

    if (state == "action" && (millis() - timeFed > 10000 || millis() - timePet > 10000)) {
        state = "mood";
        updateFace();
    } else if (state == "text" && (millis() - timeTextStart > 5000)) {
        state = "mood";
        updateFace();
    } else if (state == "blink" && (millis() - timeBlinkStart > 250)) {
        state = "mood";
        updateFace();
    }

    if (!backLightOn) {
        if ((feedButtonState == 0 && lastFeedState == 1) || (petButtonState == 0 && lastPetState == 1)) {
            backLightOn = true;
            lcd.backlight();
            updateFace();
            return;
        }
        lastPetState = petButtonState;
        lastFeedState = feedButtonState;
        
    }
    
    if (!backLightOn) {
      return;
    }

    if (feedButtonState == 0 && petButtonState == 0) {
        backLightOn = false;
        lcd.noBacklight();
    } else if (feedButtonState == 0 && lastFeedState == 1) {     

        if (canEat()) {
            Serial.println("JSDKHF");

            increaseFoodLevel();
            state = "action";
            setEyes("action");
            setMouth("happy");
            timeFed = millis();

            setMoodColor();
            lightOnStart = millis();
            moodLightOn = true;

        } else {

          if (state == "text") {
              updateFace();
              state = "mood";
          } else {
              showIsEating();
              state = "text";
              timeTextStart = millis();
          }

        }

    } else if (petButtonState == 0 && lastPetState == 1) {

        if (wantsPets()) {

            increaseAffectionLevel();
            state = "action";
            setEyes("action");
            setMouth("happy");
            timePet = millis();
            
            setMoodColor();
            lightOnStart = millis();
            moodLightOn = true;

        } else {

          if (state == "text") {
              updateFace();
              state = "mood";
          } else {
            showDoesNotWantsPets();
            state = "text";
            timeTextStart = millis();
          }
        }

    }

    lastPetState = petButtonState;
    lastFeedState = feedButtonState;
}