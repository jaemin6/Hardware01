import serial
import time

# 전역 변수
connection = None
current_distance = 0

def connection_sensor(port = 'COM7'):
    
    
def read_distance():
    
    
def main():
    if connect_sensor():
        for i in range(10):
            dist = read_distance()
            if dist:
                print(f"거리: {dist}cm")
            time.sleep(0.5)