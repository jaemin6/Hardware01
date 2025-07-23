import serial
import time
import turtle

# 설정
PORT = 'COM7'      # 아두이노 연결 포트
stopdistance = 15  # 멈추는 거리(cm)

# turtle 셋팅
def setup_turtle():
    t = turtle.Turtle()
    t.shape("turtle")
    t.color("sky blue")
    t.speed(5)
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
def read_distance(ser):  # 
    if ser and ser.in_waiting > 0:
        data = ser.readline().decode().strip()
        try:
            distance = float(data)
            return distance
        except:
            pass
    return None

# 거북이 움직이게
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
