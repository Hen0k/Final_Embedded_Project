from __future__ import print_function
from flask import Flask, render_template, request,Response
from PIC_2_PI_SPI import *
import time
import sqlite3 as sql
import threading
from facedetector import FaceDetector
import cv2
import imutils
app = Flask(__name__)

camera = cv2.VideoCapture(0)  # use 0 for web camera
fd = FaceDetector("haarcascade_frontalface_default.xml")
def gen_frames():  # generate frame by frame from camera
    while True:
        # Capture frame-by-frame
        success, frame = camera.read()  # read the camera frame
        if not success:
            break
        else:
            # resize the frame and convert it to grayscale
            frame = imutils.resize(frame, width = 300)
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            # detect faces in the image and then clone the frame
            # so that we can draw on it
            faceRects = fd.detect(gray, scaleFactor = 1.1, minNeighbors = 5,
		minSize = (30, 30))
            if(len(faceRects)>0):
                send([0x06])
            frameClone = frame.copy()

            # loop over the face bounding boxes and draw them
            for (fX, fY, fW, fH) in faceRects:
                cv2.rectangle(frameClone, (fX, fY), (fX + fW, fY + fH), (0, 255, 0), 2)

            ret, buffer = cv2.imencode('.jpg', frameClone)
            frame = buffer.tobytes()
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')  # concat frame one by one and show result


@app.route('/video_feed')
def video_feed():
    """Video streaming route. Put this in the src attribute of an img tag."""
    return Response(gen_frames(),mimetype='multipart/x-mixed-replace; boundary=frame')


@app.route('/index',methods=['GET','POST'])
def index():
    """Video streaming home page."""
    message = "ON"
    if request.method =='POST':
        message = Turn_ON(request.form['on_off'])
    return render_template('video.html',msg=message)


@app.route('/buzzer_off',methods=['POST'])
def buzzer_off():
    """Video streaming home page."""
    if request.method =='POST':
        send([0x05])
    print("off")
    return render_template('video.html',msg="ON")




def select_data():
    con = sql.connect("Sensordata.db")
    cur = con.cursor()
    cur.execute("select * from data order by  ID DESC LIMIT 10") 
    rows = cur.fetchall()
    cur.execute("select * from data")
    rows_gra = cur.fetchall()
    return rows,rows_gra

def addrec(data):
    if data[0] == 0x01:
        name = "Analog"
    elif data[0] == 0x02:
        name = "Digital"
    val = send(data)
    print (val)
    
    if name == "Digital" and val[0] > 1:
        val = [1]
    
    val = str(val[0])
    localtime = time.localtime(time.time())
    localtime = str(localtime.tm_mday)+"/"+str(localtime.tm_mon)+"/"+str(localtime.tm_year)+" "+str(localtime.tm_hour)+":"+str(localtime.tm_min)+":"+str(localtime.tm_sec)
    localtime = str(localtime)
    con = sql.connect("Sensordata.db")
    cur = con.cursor()
    #cur = con.cursor()
    cur.execute("INSERT INTO data (Name, Value, Time) VALUES (?,?,?)",(name,val,localtime))

    con.commit()
    msg = "Record successfully added"

def Turn_ON(val):
    if str(val) == "ON":
        send([0x04])
        print("------------------------------------------------------", type(val), str(val))
        return "OFF"
    elif str(val) == "OFF":
        send([0x03])
        print("off val",str(val))
        return "ON"

@app.route('/',methods=['GET','POST'])
def manipulate_data():
    threading.Timer(30, addrec,args=([0x02],)).start()
    threading.Timer(30, addrec,args=([0x01],)).start()
    rows,rows_gra = select_data()
    return render_template('index.html', result=rows,result_gra=rows_gra,len=len(rows_gra))
if __name__ == '__main__':
    app.run(host = '0.0.0.0')
    #manipulate_data()
