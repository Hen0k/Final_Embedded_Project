# User Interface of the Project
The UI has the purpose of visualizing the recorded sensor data to the user, and it has the application to control actuators that are attached to the PIC microcontroller. Since we are using SPI communication between PIC and Raspberri pi, the UI executes in the Raspberry pi. The UI has two pages for visualization purposes and control purposes. In the visualization page, it displays the data into a tabular format, and it shows the condition of the data in a graph. On the controlling page, It has a button to On and Off the actuator, and it has a face detector for detecting motions to turn on the alarm. The camera has to be attached to the Raspberry pi.

## Prerequisites
Use the package manager [pip](https://pip.pypa.io/en/stable/) to install the following packages.

```bash
pip install flask
pip install spidev
pip install imutils
pip install cv2
pip install sqlite3
```

## How to run 
First, verify all the components connected correctly on the Raspberry Pi and the PIC microcontroller. Then run the following
```bash
python index.py
```
The UI is hosted on the port 3000.
