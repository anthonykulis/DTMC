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
  
  2) I2C - Provides a simple wrapper to the Wire package found in the default Arduino SDK install. Included in this repo
  are Wire.h, Wire.cpp, and supporting classes. Please keep these with the I2C package to simplify compiling. Also note,
  some features of I2C detailed in the header and Register class have not yet been fully implemented. As of 12 April 2013,
  you can pass messages to this slave and get a response w/o the need to write your own callbacks. As an example, for
  control messages to the default I2c address (0x25), say LEFT_FORWARD (0x00) and setting speed to 255, a typical message 
  might look like Code Block A. To read say the battery voltage (requires a high and low read), ones code may look similar 
  to Code Block B. Please note, Code Block B is one of those features I havent tested yet (12 Apr 2013) is this read. I assume my math in the 
  class was correct, but I never trust my math until I see the answer!
  
        //Code Block A
        Wire.beginTransmission(0x25);
        Wire.write(ox00);
        Wire.write(0xFF);
        Wire.endTransmission();


        //Code Blcok B
        Wire.write(0x08);
        unsigned char h_val = Wire.read();
        Wire.low(0x09);
        unsigned char l_val = Wire.read();
        
        int volts = h_val << 8 | l_val;

  3) Battery - This class has an extern variable of SystemBattery and provides 3 primary functions: Battery::do_battery_diagnotics();
  Battery::start_charger(); and Battery::end_charging(). Each function name should be self documenting, yet, I will still 
  explain. Battery::do_battery_diagnostics() samples a handleful of aspects, like time, voltage, etc, to help in system
  stability. The voltage of the battery is automatically updated in the Register classes, READ_BATTERY_LEVEL_HIGH (0x08) and
  READ_BATTERY_LEVEL_LOW (0x09) and can be accessed in the above Code Block B. Battery::start_charging() does just that, 
  flips the pin allowing the uC to recharge the battery while also flaging Registers' RECHARGING variable. While charging, any message sent to move the system is defered
  to a braking call and hence ignored. Also, in a naive approach, if the voltage doesnt change in 30 seconds, an 
  error is place in Register's RECHARGING_ERROR. Battery::end_charging() also does what it says, ends the charging cycle.
  
  4)
    
