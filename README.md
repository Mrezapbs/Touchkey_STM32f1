# Touchkey_STM32f1

This is a sample Source file used for stm32f1 based on HAL driver. I've used the Read GPIO mode to see whether a Key is touched. In order to keep my interrupt handler light, I had to avoid callbacks for reading touched keys. You can use them to read Touched and Hold Keys. A combination of two or three keys can also be done using this file. 
