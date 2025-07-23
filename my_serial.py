import serial
import time

# 전역 변수
connection = None
current_distance = 0

# 센서와 연결 시도
def connection_sensor(port='COM7'):
    global connection
    try:
        connection = serial.Serial(port, 9600)
        time.sleep(2)  # 연결 안정화를 위한 대기
        print("연결 성공")
        return True
    except:
        print("연결 실패")
        return False

# 거리 데이터 읽기
def read_distance():
    global connection, current_distance
    if connection and connection.in_waiting > 0:
        data = connection.readline().decode().strip()
        try:
            distance = float(data)
            current_distance = distance
            return distance
        except:
            pass
    return None

# 메인 루프
def main():
    if connection_sensor():  # 함수 이름 수정됨
        for i in range(10):
            dist = read_distance()
            if dist is not None:
                print(f"거리: {dist}cm")
            else:
                print("읽기 실패 또는 데이터 없음")
            time.sleep(0.5)

if __name__ == "__main__":
    main()
