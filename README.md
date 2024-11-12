
# Arduino Firebase Integration for Energy Management

This repository contains an Arduino project that integrates with Firebase to monitor and control energy-related devices. It uses an ESP8266 module to connect to Wi-Fi and Firebase, providing real-time data synchronization and remote control over connected devices.

## Components and Libraries

The project uses the following components:
- **ESP8266 Wi-Fi module**: To connect to Wi-Fi and communicate with Firebase.
- **Firebase Arduino library**: For interaction with Firebase Realtime Database.
- **TimeLib and NTPClient libraries**: For getting the current time from an NTP server.

## Configuration

1. **Wi-Fi Setup**:
   - Update the following variables with your Wi-Fi network credentials:
     - `WIFI_SSID`: Your Wi-Fi network's SSID.
     - `WIFI_PASSWORD`: Your Wi-Fi network's password.

2. **Firebase Setup**:
   - Set the `FIREBASE_HOST` and `FIREBASE_AUTH` values to your Firebase project's host and authentication token.

```cpp
#define FIREBASE_HOST "your-firebase-project.firebaseio.com"
#define FIREBASE_AUTH "your-firebase-authentication-token"
```

3. **Device Setup**:
   - The code supports multiple devices identified by `MODULE_ID` and `UNIQUE_ID`. Each device can have a power control pin and charging status.

4. **Power Control**:
   - The code manages device power based on Firebase data. Each device can be turned on or off remotely, and the charging status can be monitored.

## Features

- **Remote Power Control**: Devices can be powered on or off via Firebase.
- **Real-Time Data Sync**: Device voltage and status are updated on Firebase in real time.
- **Time-based Automation**: Devices can be scheduled to turn on or off based on timestamps stored in Firebase.
- **Error Handling**: The program checks for errors when interacting with Firebase and handles them appropriately.

## Functions

- **`setValues()`**: Reads the device power and charging status from Firebase and updates the device accordingly.
- **`getTimeStampString()`**: Fetches the current timestamp from an NTP server and formats it for Firebase storage.
- **`getHourInt()`, `getMinuteInt()`, `getDayInt()`**: Retrieve the current time values to compare with Firebase-scheduled times.

## How to Use

1. Clone this repository to your local machine.
2. Open the Arduino IDE and load the provided code.
3. Set your Wi-Fi credentials and Firebase details as described in the configuration section.
4. Upload the code to the ESP8266.
5. Monitor the device’s interaction with Firebase through the Arduino Serial Monitor.

## Notes

- The Firebase Realtime Database structure should match the expected format for the device data.
- Make sure the ESP8266 is correctly connected to the internet via Wi-Fi.

## License

This project is licensed under the Apache License, Version 2.0 - see the [LICENSE](LICENSE) file for details.

