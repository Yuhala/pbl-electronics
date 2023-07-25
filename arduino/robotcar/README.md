## Re-Programming the Elego smart robot
- The aim of this readme is to provide a guide for those wishing to reprogram the Elego smart robot car.


### Setup
- Install Arduino IDE
```
sudo apt-get install arduino

```
- Or download the tar-ball, extract and run `sudo ./install`. 
- If you need serial port permissions in Linux, fix as explained here: [fix serial port permissions](https://linoxide.com/how-to-install-arduino-ide-on-ubuntu-20-04/).

## Programming the robot
- We will follow instructions in the same order as in the `tutorials` folder.
### 01 ReadMeFirst
- Open the above folder
- Read `ReadMeFirst1`: copy the folders in `CopyMeFirst` folder to the `libraries` folder of your arduino installation. For Linux users, if you installed Arduino IDE downloading the tar-ball, the `libraries` folder is a subfolder of the parent folder. Otherwise, a quick google search should tell you where to find the corresponding `libraries` folder. Windows users should follow the exact instructions in the document.
- Read `ReadMeFirst2`: for my robot kit, the 2 folders of interest are: `TB6612` and `MPU6050`. Check yours carefully and adapt accordingly as you work along.

### 02 Manual & Main Program & APP
- Open the main program folder labeled `02` and the subfolder corresponding to the results in `ReadMeFirst2` above. Mine is the `TB6612 & MPU6050` folder. This folder contains the main robot program source code: `SmartRobotCarV4.0_V1_20201229` in my case. Open the `.ino` file in your Arduino IDE.
- You observe that the main program files are `.cpp` source files as well as `.h` headers. You can open and edit these files in the Arduino IDE, or your preferred IDE. In my case I open and edit these in `vscode`. You may have some include errors in `vscode` but this should not cause issues during compilation of the `.ino` file in the Arduino IDE.


### Test compilation
- Try compiling the `.ino` file from within the Arduino IDE. If you have an inclusion error at the line: `#include <arduino.h>`, change to: `#include <Arduino.h>`. Same with the line `#include <hardwareSerial.h>`, change to `#include <HardwareSerial.h>`. 

### Upload program
- Connect the arduino board to a USB port on your PC. Verify the Arduino port; in Linux, you should have something like: `/dev/ttyUSB0`. 
- Move the switch next to the USB port to `upload`. RUpload the program to board.  If you have issues uploading the program, try unplugging the bluetooth module from the board, or the entire shield above if that is easier. This will prevent any module connected to a serial port from interfering with the program upload. Upload the program to the board again. If this, works, plug the shield back in.











## Author Info
- Peterson Yuhala
- Institute of Computer Science, UniNe, Switzerland
- petersonyuhala@gmail.com

