# Touchkey_STM32f1

This is a sample Source file used for stm32f1 based on HAL driver. I've used the Read GPIO mode to see whether a Key is touched. In order to keep my interrupt handler light, I had to avoid callbacks for reading touched keys. You can use it to read Touched and Hold Keys. A combination of two or three keys can also be done using this file. 
Using Oscilloscope, I found out that the minimum time interval between two KEY TOUCH is about 100ms. So You need a 100ms second debounce. The variable "FunctionalStatus.Touchkeys.TouchKeyCounter" should be put in a hundred milliseconds Timer. In case of a Key touch this variable adds up. 
This file just wanna show how I code. Any feedback will be appreciated! 
