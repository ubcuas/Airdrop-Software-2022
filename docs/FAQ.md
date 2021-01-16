# FAQ

---

| problem                                                     | solution                                                     |
| ----------------------------------------------------------- | ------------------------------------------------------------ |
| platformio(pio) cannot be installed/trapped when installing | use `pip install platformio` to install pio, and reinstall platformio in vscode. Worst case, if pip install successful, use terminal to execute commands. |
|` [upload] could not open port /dev/ttyACM0: [Errno 13] Permission denied: '/dev/ttyACM0'` |https://docs.platformio.org/en/latest/faq.html#platformio-udev-rules|
|Teensy 4.0 I2C problem(Wire1 and Wire): For some reason, Wire1 onlyworks for BN055, and Wire works for only BMP280|                                                              |Use Wire1 for BN055, Wire for BMP280
|                                            |                                                              |

