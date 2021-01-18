# FAQ

---

| problem                                                     | solution                                                     |
| ----------------------------------------------------------- | ------------------------------------------------------------ |
| platformio(pio) cannot be installed/trapped when installing | use `pip install platformio` to install pio, and reinstall platformio in vscode. Worst case, if pip install successful, use terminal to execute commands. |
|` [upload] could not open port /dev/ttyACM0: [Errno 13] Permission denied: '/dev/ttyACM0'` |https://docs.platformio.org/en/latest/faq.html#platformio-udev-rules|
|Teensy 4.0 I2C problem(Wire1 and Wire): For some reason, Wire1 onlyworks for BN055, and Wire works for only BMP280|                                                              |Use Wire1 for BN055, Wire for BMP280
|Teensy freeze: When uploading, nothing happens and it keeps hanging. Cannot upload to Teensy, and Serial monitor display nothing or freeze|Your code is bugged at run-time. This could be caused by: Runtime memory leak(you access something that is removed); Serial print void(you ask serial to print fault data type or print erroneous data)|

