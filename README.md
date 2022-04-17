# bvf_play

Add-In for the Casio fx-9860GII to play [BVF](https://github.com/kizza7984/bvf_encode) video files.

![Rick Astley](pics/pic1.png)
![Bad Apple](pics/pic2.png)

Images are from the SDK emulator but it works the same on the real device. An issue is that each frame takes a different amount of time to display and there is no way of accounting for this accurately because the SDK does not provide any time-keeping system, if this wasn't the case the frame rate value in the file could be used to display the video at the right speed.

## Installation

Download the Add-In file `BVFPLAY.G1A` from the [Releases](https://github.com/kizza7984/bvf_play/releases) and install it. The easiest way to install it is to connect the calculator as a storage device via USB cable, then place the file in the root directory.

## Usage

1. Place a BVF file named `output.bvf` in the root directory of the calculator's storage memory.
2. Run the Add-In.
