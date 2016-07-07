README
******************************
*							 *
*	Broentech Solutions AS   *
*							 *
* Kongeveien 79, 3188 Horten *
*		   Norway			 *
*							 *
******************************
*							 *
*		--	SFILT	--		 *
*							 *
******************************

by : Stian Broen
	 stian@broentech.no


	What is SFILT ?
	
SFILT is an opensource GUI project used to explore some image-filtering algorithms in OpenCV using Qt5


	How do I build it?
	
First you need (for Windows) :
	* Qt 5.X
	* OpenCV 3.X
	* (Optional) Visual Studio
	* Git
	
Set the following environmental variables :
	* OPENCV_DIR (on my system its C:\source\libs\OpenCV\opencv-3.1\opencv\build\x64\vc12)
	* QTDIR (on my sustem its C:\Qt\5.7\msvc2013_64)
	
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

