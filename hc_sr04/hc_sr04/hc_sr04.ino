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

  setColor(false, false, false);  // LED 끄기
}

void setColor(bool r, bool g, bool b) {
  digitalWrite(redPin, r ? HIGH : LOW);
  digitalWrite(greenPin, g ? HIGH : LOW);
  digitalWrite(bluePin, b ? HIGH : LOW);
}

// 8가지 색상 배열 (RGB 조합)
bool colors[8][3] = {
  {true, false, false},   // 빨강
  {false, true, false},   // 초록
  {false, false, true},   // 파랑
  {true, true, false},    // 노랑
  {true, false, true},    // 자홍
  {false, true, true},    // 청록
  {true, true, true},     // 흰색
  {false, false, false}   // 끔
};

void loop() {
  int currentState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && currentState == LOW) {
    isRunning = true;
    count = 0;
  }
  lastButtonState = currentState;

  if (isRunning && count < 4) {  // 2회전 = 4번 움직임
    myservo.write(0);
    setColor(colors[count % 8][0], colors[count % 8][1], colors[count % 8][2]);
    delay(300);
    
    myservo.write(90);
    setColor(colors[(count+1) % 8][0], colors[(count+1) % 8][1], colors[(count+1) % 8][2]);
    delay(300);
    
    count++;
  }

  if (isRunning && count >= 4) {
    Serial.println("MOVE");
    isRunning = false;
    setColor(false, false, false); // LED 끄기
    delay(1000);
  }
}
