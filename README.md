# AviosysUSBNetpower8800-
A super simplified version of the "SDK" example from Aviosys USB Net Power 8800

Inside the VS2008 is the simplest example possible for accessing the power switch in c++

If you just want to use this in Unity, you can just drag the files inside the Unity folder 
into a Unity project. The USBPower script by default will toggle the power every 3 seconds. 
You can delete that whole update function. From anywhere else in any other srcipt you can just:

USBPower.Init();
to open the connection

USBPower.Toggle(true);
after init, you can turn the switch on

USBPower.Toggle(false);
after init, you can turn the switch off too!

USBPower.Close();
make sure to close the connection when you quit your app. 


This provided DLL will work in any other app too. Unity is not required. 