import turtle
import serial
import time

# 시리얼 포트 연결
try:
    ser = serial.Serial('COM7', 9600, timeout=1)  # 아두이노 포트에 맞게 변경
    time.sleep(2)  # 연결 안정화 대기
    print("시리얼 연결 완료")
except:
    print("시리얼 연결 실패")

# 거북이 셋팅
t = turtle.Turtle()
t.shape("turtle")
t.color("sky blue")
t.penup()
t.goto(-200, 0)

# 거북이 이동
def move_turtle():
    print("진격하라!!!!")
    t.forward(80)

# 메인 루프
while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode().strip()
        print(f"받은 메시지: {line}")
        if line == "MOVE":
            move_turtle()

