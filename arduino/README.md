## Synopsis

This code will read and debounce switch presses from the 
skeeball machine and act as HID Keyboard. I find the I/O 
and high level access undesirable and this seperation 
allows for a more definitive and robust system.

HID vs Serial was used to allow easier intergration by 
either using gaming libraries, like pygame, or using
STDIN and no hassle of setting terminal parametes and
opening proper device.

It may be compile option to be be serial or HID in future.

## Installation

Adjust code ass needed for I/O initalization and 
debounce and output paramters. After words, compile
and it should send keypresses depending on your
settings.

This code should be deployed on a leanardo arduino device
so it can emulate a HID. 

## Contributors

David "supersoaker" Goldberg

## License

Distributed under MIT Licenses

