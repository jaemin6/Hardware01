#include <Servo.h>

Servo myservo;

const int buttonPin = 2;
const int redPin = 11;
const int greenPin = 12;
const int bluePin = 13;

int lastButtonState = HIGH;
bool isRunning = false;
int count = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(6);
  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // LED 끄기 (공통 음극이라 LOW 끔)
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void setColor(bool r, bool g, bool b) {
  digitalWrite(redPin, r ? HIGH : LOW);
  digitalWrite(greenPin, g ? HIGH : LOW);
  digitalWrite(bluePin, b ? HIGH : LOW);
}

void loop() {
  int currentState = digitalRead(buttonPin);

  // 버튼 눌림 감지
  if (lastButtonState == HIGH && currentState == LOW) {
    isRunning = true;
    count = 0;
    setColor(true, false, false);  // 빨간색 LED 켜기
  }
  lastButtonState = currentState;

  if (isRunning && count < 2) {
    myservo.write(0);
    delay(300);
    myservo.write(90);
    delay(300);
    count++;
  }

  if (isRunning && count >= 2) {
    Serial.println("MOVE");
    isRunning = false;
    setColor(false, true, false);  // 초록색 LED 켜기 (작동 완료 표시)
    delay(1000);
    setColor(false, false, false); // LED 끄기
  }
}
