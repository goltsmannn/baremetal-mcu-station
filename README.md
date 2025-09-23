Implementing a station reading data from sensors and displaying it on an LED Display in bare-metal C.
Implemented:
1) UART for serial communication (interrupt-driven, circular buffer used for queueing data)
2) I2C to communicate with temperature sensor (bit-banging)
3) GPIO management
4) 7-segment display management 
4) Other Utils 

TODO:
1) Multiplexing LED displays
2) Mini-RTOS orchestrating tasks
3) FAT16 for microSD data transfer
