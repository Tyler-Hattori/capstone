#!/usr/bin/env python3
from flask import Flask
from flask import render_template
import RPi.GPIO as rpi
import time

app= Flask(__name__)

pinwf,pingf,pinnav,pinpg,pine,pinf,pinb,pinl,pinr= 11,12,13,15,16,35,36,37,38

rpi.setwarnings(False)
rpi.setmode(rpi.BOARD)
rpi.setup(pinwf, rpi.OUT)
rpi.setup(pingf, rpi.OUT)
rpi.setup(pinnav, rpi.OUT)
rpi.setup(pinrd, rpi.OUT)
rpi.setup(pinf, rpi.OUT)
rpi.setup(pinb, rpi.OUT)
rpi.setup(pinl, rpi.OUT)
rpi.setup(pinr, rpi.OUT)
rpi.output(pinwf, 0)
rpi.output(pingf, 0)
rpi.output(pinnav, 0)
rpi.output(pine, 0)
rpi.output(pinpg, 0)
rpi.output(pinf, 0)
rpi.output(pinb, 0)
rpi.output(pinl, 0)
rpi.output(pinr, 0)
print("Done")

@app.route('/')
def index():
    return render_template('webpage.html')

@app.route('/wall_follow')
def led1on():
    rpi.output(pinwf,1)
    return render_template('webpage.html')

@app.route('/gap_follow')
def led1off():
    rpi.output(pingf,1)
    return render_template('webpage.html')

@app.route('/navigate')
def led2on():
    rpi.output(pinnav,1)
    return render_template('webpage.html')

@app.route('/puppy_guard')
def led2off():
    rpi.output(pinpg,1)
    return render_template('webpage.html')

@app.route('/explore')
def led2off():
    rpi.output(pine,1)
    return render_template('webpage.html')

@app.route('/forward')
def led3on():
    rpi.output(pinf,1)
    return render_template('webpage.html')

@app.route('/backward')
def led3off():
    rpi.output(pinb,1)
    return render_template('webpage.html')

@app.route('/left')
def led3off():
    rpi.output(pinl,1)
    return render_template('webpage.html')

@app.route('/right')
def led3off():
    rpi.output(pinr,1)
    return render_template('webpage.html')

if __name__=="__main__":
    print("Start")
    app.run(debug=True, host='169.231.179.34')
