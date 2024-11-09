#include <LiquidCrystal_I2C.h>
#include <Wire.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

const int ledPin = 7;
const int buzzerPin = 8;
const int buttonPin = 13;


int lastButtonState;
int currentButtonState;

bool metronomeState = false;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(buttonPin, INPUT);
  currentButtonState = digitalRead(buttonPin);
}

void loop() {
  lastButtonState = currentButtonState;
  currentButtonState = digitalRead(buttonPin);

  lcd.setCursor(0, 0);
  lcd.print("     Tempo:     ");

  int sensorValue = analogRead(A0);
  int pause = map(sensorValue, 0, 1023, 100, 1000);
  String bpm = String(60000 / pause);
  

  lcd.setCursor(0, 1);
  String tempo = "    " + bpm + " BPM";
  lcd.print(tempo);



  if (lastButtonState == LOW && currentButtonState == HIGH) {
    if(metronomeState == false) {
      metronomeState = true;
      Serial.println("Metronome is on");
    }
    else {
      metronomeState = false;
      Serial.println("Metronome is off");
    }
  }

  if (metronomeState == true) {

    // Metrome beep and flicker
    tone(buzzerPin, 4000);
    digitalWrite(ledPin, HIGH);

    // 10 ms delay for the beep and flicker
    delay(10);
    
    noTone(buzzerPin);
    digitalWrite(ledPin, LOW);
    delay(pause - 10);
    lcd.clear();
  }
  else {
    delay(pause);
    lcd.clear();
  }
}
