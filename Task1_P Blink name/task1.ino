#define LED_PIN LED_BUILTIN

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  blinkLetter('S');
  delay(1500);
  blinkLetter('I');
  delay(1500);
  blinkLetter('M');
  delay(1500);
  blinkLetter('A');
  delay(1500);
  blinkLetter('R');
  delay(3000);  // wait before repeating
}

void blinkDot() {
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  delay(200);
}

void blinkDash() {
  digitalWrite(LED_PIN, HIGH);
  delay(750);
  digitalWrite(LED_PIN, LOW);
  delay(250);
}

void blinkLetter(char c) {
  switch (toupper(c)) {
    case 'S':
      blinkDot();
      blinkDot();
      blinkDot();
      break;
    case 'I':
      blinkDot();
      blinkDot();
      break;
    case 'M':
      blinkDash();
      blinkDash();
      break;
    case 'A':
      blinkDot();
      blinkDash();
      break;
    case 'R':
      blinkDot();
      blinkDash();
      blinkDot();
      break;
    default:
      break;
  }
}
