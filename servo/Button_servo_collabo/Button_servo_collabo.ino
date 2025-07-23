#include <Servo.h>

Servo myservo;

const int buttonPin = 2; // 버튼 핀
int lastButtonState = LOW;
bool isRunning = false;
int count = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(6);  // ✅ 서보모터 6번 핀에 연결
  pinMode(buttonPin, INPUT_PULLUP);  // 풀업저항 사용 (안 누르면 HIGH)
}

void loop() {
  int currentState = digitalRead(buttonPin);

  // 버튼이 눌렸을 때 (HIGH → LOW)
  if (lastButtonState == HIGH && currentState == LOW) {
    isRunning = true;
    count = 0;
  }
  lastButtonState = currentState;

  // 서보 2회 동작
  if (isRunning && count < 2) {
    myservo.write(0);   // 0도
    delay(300);
    myservo.write(90);  // 90도
    delay(300);
    count++;
  }

  // 2회 끝나면 시리얼 전송 후 멈춤
  if (isRunning && count >= 2) {
    Serial.println("MOVE");  // 시리얼 통신으로 신호 전송
    isRunning = false;
    delay(1000);  // 약간의 대기 시간
  }
}
