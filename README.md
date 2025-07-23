# Hardware01


## 초음파 센서에 따른 거북이 제어
### 주요기능
#### 1. Arduino 초음파 센서와 Python 연동

#### 2. 장애물이 없으면 거북이 전진, 감지되면 멈춤

#### 3. 실시간 거리 출력 (Serial → Python)

#### 4. 0.05초 간격으로 거리 데이터 지속 확인



## MVP (Minimum Viable Product): 최소 기능
### 프로젝트 MVP 목표
#### 1. 아두이노 초음파 센서에서 거리 데이터를 보냄

#### 2. 파이썬에서 해당 데이터를 읽음

#### 3. 특정 거리(stopdistance)보다 멀면 거북이 앞으로 이동

#### 4. 가까우면 즉시 멈추는 반응을 구현



## 코드 동작 설명

### 필요한 라이브러리 불러오기
#### 1. import serial
#### 2. import time
#### 3. import turtle


### 거북이 셋팅, 기본 설정(색상, 속도, 모양)
#### def setup_turtle(): 


### 아두이노와 시리얼 포트를 통해 연결을 시도, 실패할 경우 False 반환

#### def connection_sensor(port='COM7'):



### 아두이노에서 전송된 거리 값을 읽음

#### def read_distance(ser):


    
### 초음파 센서를 감지, 거북이 감지 값에 따라 이동, 정지, 재이동

#### def move_turtle(t, ser):



### 메인 함수 (센서를 연결, 거북이 셋팅, 거북이 이동)

#### def main():


