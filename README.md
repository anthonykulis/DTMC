Provided in this repo are classes to help with the Dagu Thumper Motor Controller.
_________________________________________________________________________________

The intention of this package of classes is to provide I2C slave support similar to black box devices found in 
such things as inertia sensors, but also provide userspace hooks incase the developer was to only use 
this systems uC as the primary controller. 

Typical usage as an I2C slave device is to:

    #include <Register.h>
    #include <I2C.h>
    #include <Battery.h>
    #include <Saftey.h>
    #include <MotorControl.h>
    
    MotorControl mc;
    
    void setup(){}
    
    void loop(){
    
      mc.update();
      
    }
    
By including these 5 classes, your I2C callback events are defined and automatically handle the register calls. MotorControl
provides all the needed functionality to mimic the loop() event by simply calling MotorControl::update(); Detailed information
about each class are as follows:

Class List:

  1) Register - Provides a psuedo register to hold control and state values. This is the primary class needed by nearly 
  all other classes. See the header file for the addressing scheme. As of 12 April 2013, the .gnumeric file is out-of-date.
  This class is externed to DataRegister and is available upon include of header file. It provides 2 types of registers,
  read only and read-write. It also mimics file io such that there are open, write, read, and close calls. Also, there are
  3 open flags: REG_READ_ONLY, REG_READ_WRITE, and REG_MASTER_MODE. Only on handle can access a register at a time, and
  only registers available for read/write can be opened by REG_READ_WRITE. REG_MASTER_MODE is intended for the I2C class 
  and allows reading and writing even if hooked by a handle of REG_READ_ONLY or REG_READ_WRITE. As of 12 April 2013,
  most registers have been tested and should perform nicely. 
  
  2) 


