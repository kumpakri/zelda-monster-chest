const int BUZZER_PIN = 8;
const int LID_PIN = 2;
const int LIGHTS_PIN = 4;

// Notes in the melody:
int melody[] = {
  349, 440, 523, 494, 587, 698, 1046
};

// Note durations: 4 = quarter note, 8 = eighth note, etc.
int noteDurations[] = {
  8, 8, 8, 8, 8, 8, 2
};

bool isLidOpen = true;

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 bits per second
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LIGHTS_PIN, OUTPUT);
  pinMode(LID_PIN, INPUT);
  Serial.println("Setup complete. Open the lid to play the melody.");
}

void loop() {
  // Check if the lid is open
  // The lid has an IR optical gate sensor. When the lid is closed
  // the optical path is obstructed and sensor (LID_PIN) returns 
  // LOW. When the lid opens the optical path is cleared and sensor 
  // returns HIGH. 
  if (not isLidOpen and digitalRead(LID_PIN) == HIGH) {
    Serial.println("Lid open.");
    tunOnLights();
    Serial.println("Lights on.");
    playMelody();
    isLidOpen = true;
    delay(1000); // Wait for a second before allowing another play
  } if (isLidOpen and digitalRead(LID_PIN) == LOW) {
    Serial.println("Lid closed.");
    digitalWrite(LIGHTS_PIN, LOW);
    Serial.println("Lights off.");
    isLidOpen = false;
  }
}

void playMelody() {
  // Iterate over the notes of the melody:
  for (unsigned int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) {

    // To calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER_PIN, melody[thisNote], noteDuration);

    // To distinguish the notes, set a minimum time between them.
    // The note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    // Stop the tone playing:
    noTone(BUZZER_PIN);
  }
}

void tunOnLights()
{
  // for better effect lights are turned on with a tiny delay
  delay(500);
  digitalWrite(LIGHTS_PIN, HIGH);
}
