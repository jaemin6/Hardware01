# Hardware01


## 1. 초음파 센서에 따른 거북이 제어
### 주요기능
#### 1. Arduino 초음파 센서와 Python 연동

#### 2. 장애물이 없으면 거북이 전진, 감지되면 멈춤

#### 3. 실시간 거리 출력 (Serial → Python)

#### 4. 0.05초 간격으로 거리 데이터 지속 확인



## 2. MVP (Minimum Viable Product): 최소 기능
### 프로젝트 MVP 목표
#### 1. 아두이노 초음파 센서에서 거리 데이터를 보냄

#### 2. 파이썬에서 해당 데이터를 읽음

#### 3. 특정 거리(stopdistance)보다 멀면 거북이 앞으로 이동

#### 4. 가까우면 즉시 멈추는 반응을 구현



## 3. 코드 동작 설명

### 필요한 라이브러리 불러오기
#### 1. import serial
#### 2. import time
#### 3. import turtle


### 거북이 셋팅, 기본 설정(색상, 속도, 모양)
 ```
def setup_turtle():
    t = turtle.Turtle()
    t.shape("turtle")
    t.color("sky blue")
    t.speed(5)
    return t
``` 


### 아두이노와 시리얼 포트를 통해 연결을 시도, 실패할 경우 False 반환

```
def connection_sensor(port='COM7'):
    try:
        ser = serial.Serial(port, 9600)
        time.sleep(2)
        print("연결 성공")
        return ser
    except Exception:
        print("연결 실패")
        return False
```



### 아두이노에서 전송된 거리 값을 읽음

```
def read_distance(ser):  # 
    if ser and ser.in_waiting > 0:
        data = ser.readline().decode().strip()
        try:
            distance = float(data)
            return distance
        except:
            pass
    return None
```


    
### 초음파 센서를 감지, 거북이 감지 값에 따라 이동, 정지, 재이동

 ```
def move_turtle(t, ser):
    dist = read_distance(ser)
    if dist is not None:
        print(f"거리: {dist}cm, 장애물 거리: {stopdistance}")
        if dist > stopdistance:
            t.forward(20)
        else:
            print("장애물 감지, 멈춤")
    else:
        print("거리 데이터 없음")

    turtle.Screen().ontimer(lambda: move_turtle(t, ser), 50)
```



### 메인 함수 (센서를 연결, 거북이 셋팅, 거북이 이동)

```
def main():
    ser = connection_sensor()
    if not ser:
        print("연결 실패")
        return

    t = setup_turtle()
    move_turtle(t, ser)
    turtle.done()

if __name__ == "__main__":
    main()
```

# Hardware02


## Arduino + Python Turtle 프로젝트



## 서브모터 작동에 따른 작동시 거북이 제어


### 주요 기능
#### 1. 버튼을 누르면 서보모터가 2회 동작

#### 2. RGB LED가 다양한 색으로 깜빡임

#### 3. 아두이노가 `"MOVE"` 시리얼 신호를 전송

#### 4. 파이썬에서 이 신호를 받아 거북이(Turtle)가 전진



## 아두이노 회로 구성
```
- 서보모터: D6번 핀
- 누름버튼: D2번 핀 (`INPUT_PULLUP`)
- RGB LED
  - Red: D10
  - Green: D11
  - Blue: D12
 ```



## 실행 순서

### 1. 아두이노 보드에 코드 업로드

### 2. 버튼을 누르면서보 2회 동작, RGB LED 깜빡임

### 3. "MOVE" 문자열 시리얼 전송

### 4. 파이썬에서 "MOVE" 수신 시, 거북이 전진



## 핵심 동작 

### Arduino (아두이노)
- 버튼 누름 감지: `digitalRead(buttonPin)`
- 서보 2회 동작:
  - `myservo.write(0)`
  - `myservo.write(90)`
- RGB 색 깜빡임: `analogWrite(redPin, random(0, 256))`
- 시리얼 전송: `Serial.println("MOVE")`

### Python (파이썬)
- 시리얼 수신: `ser.readline().decode().strip()`
- 거북이 전진: `t.forward(50)`
