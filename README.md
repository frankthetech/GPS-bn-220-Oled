# GPS-bn-220-Oled
  
  A simple but working example of  GPS unit with display on an Oled.
  
  I got this working with a Teensy LC (could use other boards too) hooked up to a BN-220 GPS and basic I2C Oled display.
  
  Hook up the BN-220 to the serial1 port, BN-220 Tx-->LC Rx (pin#0) and BN-220 Rx-->LC Tx (pin#1)
  
  The Oled to +3.3v - Gnd - SCL-->Lc pin#19 - SDA-->LC pin#18
  
  You may need to add the Librarys required.
