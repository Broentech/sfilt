# SFILT

SFILT is an opensource GUI project used to explore some image-filtering algorithms in OpenCV using Qt5

by Stian Broen, 2016
(C) Broentech Solutions AS
stian@broentech.no

## Installation

How do I build it?
	
First you need (for Windows) :

1. Qt 5.X
2. OpenCV 3.X
3. (Optional) Visual Studio
4. Git
	
Set the following environmental variables

OPENCV_DIR (on my system its C:\source\libs\OpenCV\opencv-3.1\opencv\build\x64\vc12)

QTDIR (on my sustem its C:\Qt\5.7\msvc2013_64)
	
Open a shell according to your setup. I use Qt 5.7 64-bit for Desktop (MSVC 2013)

Go to /scripts
run 
setEnv.cmd

go to /source
run
qmake -r
make

(if you have Visual Studio) :
run
qmake -r -tp vc
cmake

You can open the project in Visual Studio now
go to /scripts
run
vcstart.cmd
browse to your sln file and open it
Click 'play'.. and play ;)

## Usage

The program is pretty simple. It can be used as a starting point for your image processing application.
And it can be used to explore some of the possibilities within OpenCV.

1. Import an image. 
2. Right-click to open the processing menu
3. Add the filters you want to explore. You can stack them.
4. You can go to 'RGB' or 'HSV' to edit the channels separately
5. You can do some histogram processing
6. You can merge the channels into 1 image again


## License

LGPL v3, see separate file

