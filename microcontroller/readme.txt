Compiling the code requires first successfully setting up the Arduino-Makefile project (https://github.com/sudar/Arduino-Makefile). This project offers scripts that allow you to easily build and upload your program to an arduino.
Unfortunately getting the project to work requires a bit of tweaking with configuration files and installing extra programs and this will ultimately depend on the operating system and software already installed.

The structure of this nut sorter project also follows the Bare-Arduino-Project (https://github.com/sudar/Arduino-Makefile). This project offers a higher layer of structure to the nut sorter code base.

There also seems to be a bug with the Arduino-Makefile scripts that should be pointed out. When a library in the lib folder includes another library, the compiler will complain that it can’t find the files. One way to solve this is to include any headers you will need directly in the main cpp file.

The first step that should be taken when trying to get this working would be to download the latest copy of the arduino IDE and extract it in the the folder 'arduino-ide'.
Then go to the start configuring the make file in 'src/main'. Once everything is setup correctly you will be able to compile the code base by just running 'make' in the terminal. Then you will also have the option to use 'make upload' and 'make monitor'.
