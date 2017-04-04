# simple_alarm
This is my first Github project. \o/

In this simple alarm clock repository you find:
* my source code to the program 
* solution to the program
* an alarm buzzer sound clip

## Info
This program just simulate a simple alarm clock. The default program will only store 3 times, but this 
can be changed manually in the program. <br />
* The full alarm buzzer sound clip is from http://soundbible.com/2061-Loud-Alarm-Clock-Buzzer.html
* The website for coverting sound from mp3 to wav and clipping is from http://online-audio-converter.com/

## Usage

1. Install Visual Studio, if you haven't already <br />
* If you don't have Visual Studio, please download Visual Studio at https://www.visualstudio.com/ and install it. 
<br /><br />

2. Clone repository 

```bash
   git clone --depth 1 https://github.com/lilylei95/simple_alarm.git
```
<br />


3. Open up visual studio
There two ways you can open this:
* You can open .sln file from simple_alarm/Alarm/Alarm.sln <br />
                  or <br />
* Open visual studio then File > Open > Open Project > find the Alarm.sln file
<br />

4. Changing location of where you play sound
The current program the location of alarm buzzer sound is located in my directory, but you have to change it to yours. 
Inside of simple_alarm/Code/Source code/alarm.cpp on line 284, please change this line 

``` bash
#orginal line in simple_alarm/Code/Source code/alarm.cpp on line 284
PlaySound("$(SolutionDir)/Alarm_v1/Loud_Alarm_Clock_Buzzer.mp3", 0, 0);
#change it to 
PlaySound(/* location of Loud_Alarm_Clock_Buzzer.mp location */, 0, 0);
```
5. Build and use


