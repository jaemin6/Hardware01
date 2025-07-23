import serial
import time
import turtle

# 설정
PORT = 'COM7'      # 아두이노 연결 포트
stopdistance = 10  # 멈추는 거리(cm)

# turtle 셋팅
def setup_turtle():
    t = turtle.Turtle()
    t.shape("turtle")
    t.color("sky blue")
    t.speed(1)
    return t

# 시리얼 연결
def connection_sensor(port='COM7'):
    try:
        ser = serial.Serial(port, 9600)
        time.sleep(2)
        print("연결 성공")
        return ser
    except Exception:
        print("연결 실패")
        return False

    
    
# 거리 데이터 읽기
'''def read_distance():
    
    
    
    
# 메인 함수  
def main():'''