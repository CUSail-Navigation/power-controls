# power-controls
Monorepo for remote power controls to the boat. This setup is independent of primary boat functionality; even if the boat software freezes or if there is some hardware failure, this controls system should still be usable. 

An Arduino Nano is placed on the power controls PCB and toggles 4 relays based on inputs it recieves from an Xbee module. On the other end of the network, there is a switch board (separate from the primary boat controls mechanism) which a user can use to toggle power to each of these relays.

## Hardware
This code is designed to run on an Arduino Nano, with an accompinying Xbee module.

Right now, we are using an Arduino Nano dupe on both ends, an Elegoo Nano. We use VSCode with the Platform.io extension as the development environment. 

### For Fiona + Nicole
I created the boat-code file for the part of the network on the boat, you will have to make another file for the controller code (probably named controller-code or something). I'll walk you through doing it, but note the following (writing it now while I remember):

 - You should program the board in C++. This code specifically does not have crazy timing requirements and could probably be done more easily in Python, but it is generally bad practice to write microcontroller code in Python because C/C++ code tends to run faster (vast oversimplification but whatever). Good opportunity to get into the wonders and joys of C programming now!

 - The boat-code file has not been rigirously tested, so there might be bugs. If you run into issues and are confident that your code is correct, it is probably my fault lmao.

 - For creating the Platform.io project:
    1. Click the alien
    2. Select "create new project" and name it whatever (probably controller-code)
    3. Search "Arduino Nano" under board and select "Arduino Nano ATmega328 (new bootloader)"
    4. Deselect "Use default location" and navigate to the project folder

