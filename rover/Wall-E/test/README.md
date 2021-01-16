# Testing
---
## Remote testing
We will use platformio's remote testing feature. Please see more detailed guide at [Remote development](https://docs.platformio.org/en/latest/core/userguide/remote/cmd_device.html#pio-remote-device-list)

### Set up on Raspberry pi 4

- create a pio account ```pio account login```

```bash
# Install pio
python3 -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"

# copy udev
curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/master/scripts/99-platformio-udev.rules | sudo tee /etc/udev/rules.d/99-platformio-udev.rules

# updating library
sudo apt-get install libssl-dev

pio upgrade --dev
pio update

pio remote agent start
```

FAQ: https://community.platformio.org/t/how-to-remote-upload-to-teensy4/12242/4

probably need to fix the teensy_load_cli. By default from PI, this is supported MCUs"

```bash
Supported MCUs are:
 - at90usb162
 - atmega32u4
 - at90usb646
 - at90usb1286
 - mkl26z64
 - mk20dx128
 - mk20dx256
 - mk66fx1m0
 - mk64fx512
 - TEENSY2
 - TEENSY2PP
 - TEENSYLC
 - TEENSY30
 - TEENSY31
 - TEENSY35
 - TEENSY36
```



Set up on Arch

https://github.com/conda/conda/issues/9957

```bash
pip install certifi
cd /usr/lib
sudo ln -s libffi.so.7.1.0 libffi.so.6

pio update
```



### Test with remote

 ```bash
pio remote test --environment teensy40_test
 ```



## Hardware stress Testing

| Name                        | description                                                  | Result |
| --------------------------- | ------------------------------------------------------------ | ------ |
| Hardware sensor stress test | Testing if the Teensy will run out of RAM or something, or some thread will hang after a long time, by keeping Teensy with all sensor connected running for a long time. Since the whole flight window is 45 minutes, we aim for 45X60=2700 seconds. | 3573s  |
|                             |                                                              |        |
|                             |                                                              |        |
|                             |                                                              |        |

