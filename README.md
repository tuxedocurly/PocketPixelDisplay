# Pocket Pixel Display - A portable, hackable LED Display

Welcome to the Pocket Pixel Display! I created this project to give me a customizable LED matrix platform to perform a wide variety of tasks. Use the display for product photography, show important notifications on the go, or load up WLED to add some animated ambiance to your workspace.

![DSCF0302](https://github.com/user-attachments/assets/1e4dc1f4-eb3c-4769-8af0-3f93a686b83f)

Below, you'll find everything you need to build your own Pocket Pixel Display. If you prefer a video guide, check out my *[YouTube channel](https://www.youtube.com/@TuxedoMakes).*

## <img src="https://cdn.buymeacoffee.com/buttons/bmc-new-btn-logo.svg" alt="Buy me a coffee" width="25"/> Support This Project (and Fuel Open Source!)

This project is a labor of love, built during my spare time. If you've found this project helpful, interesting, or just plain awesome, consider checking out [my shop](https://buymeacoffee.com/tuxedomakes/extras) where I sell PCBs and parts to make some of my projects, or buy me a coffee!

**Your support helps me:**

*   Dedicate more time to improve designs
*   Experiment with new features and ideas
*   Kickstart other open-source projects you might love

<a href="https://buymeacoffee.com/tuxedomakes"><img src="https://img.buymeacoffee.com/button-api/?text=Buy me a coffee&emoji=&slug=tuxedomakes&button_colour=FFDD00&font_colour=000000&font_family=Cookie&outline_colour=000000&coffee_colour=ffffff" /></a>

Even a small coffee-sized contribution goes a long way in fueling my passion for sharing my projects with you all. If you use the shop, you'll get a useful part for your next project, plus my eternal gratitude!

**Thank you for being awesome!**

---

## Table of Contents

- [Introduction](#introduction)
- [Materials & Tools](#materials--tools)
- [Hardware Assembly](#hardware-assembly)
  - [3D Printing & Case Preparation](#3d-printing--case-preparation)
  - [Battery & Power Setup](#battery--power-setup)
  - [LED Matrix Preparation](#led-matrix-preparation)
  - [Prepping the D1 Mini](#prepping-the-d1-mini)
  - [Wiring & Final Assembly](#wiring--final-assembly)
- [Software Setup](#software-setup)
  - [Installing WLED](#installing-wled)
  - [Installing the Custom Arduino Code (Gmail Notifications)](#installing-the-custom-arduino-code-gmail-notifications)
- [Customization Ideas](#customization-ideas)
- [License](#license)

---

## Introduction

The bill of materials (BOM) for this project is ~$20 - $40 depending on where you get your materials, and you'll need ~1 hour to assemble to project.

---

## Materials & Tools

### Components

- **8×8 LED Matrix** (WS2812B/NeoPixel) ([Amazon](https://amzn.to/4b0lBRX))
- **D1 Mini Microcontroller** ([Amazon](https://amzn.to/4gIIWJ6))
- **LiPo Battery** (1000mAh or better) ([Amazon](https://amzn.to/4kdQvL9))
- **Charge Controller with 5V Boost Board** ([Amazon](https://amzn.to/3EBV8yh))
- **On/Off Toggle Switch** ([Amazon](https://amzn.to/3EFhYF2))
- **JST Connector** (optional, for easy battery connection) ([Amazon](https://amzn.to/3EBzHND))
- **M2 Screws** ([Amazon](https://amzn.to/3EAxHp1))
- **Heat Set Inserts** ([Amazon](https://amzn.to/41gzCba))
- **Wires & Soldering Supplies** 
- **Double-Sided Tape** (for securing the battery) ([Amazon](https://amzn.to/4jXWT8S))
- **3D-Printed Case Parts** ([Maker World](https://makerworld.com/en/models/1095883#profileId-1090255))

### Tools

- 3D Printer (or access to one via a library/makerspace) ([Bambu Lab A1 Mini](https://amzn.to/42XF7ge))
- Soldering Iron & Solder ([Amazon](https://amzn.to/3COL2te))
- Multimeter ([Amazon](https://amzn.to/3Qmp3wV))
- Screwdriver (for M2 screws)
- Heat Shrink Tubing ([Amazon](https://amzn.to/4jWDYeJ))

![components](https://github.com/user-attachments/assets/7668eaef-142d-4428-ada0-aa6c4e7069e9)

---

## Hardware Assembly

### 3D Printing & Case Preparation

1. **Print the Case Parts:**  
   Use the linked 3D design files (or the STLs in this repo) to print all case components.
     - [Case Files on Maker World](https://makerworld.com/en/models/1095883#profileId-1090255)
  
![disassembled_high_quality](https://github.com/user-attachments/assets/bbce8a02-db08-4984-89e3-760cddb17643)

3. **Install Heat Set Inserts:**  
   - In the **top case**, install 4 heat set inserts that will later secure the bottom case and top case together.
   - In the **bottom case**, install 2 heat set inserts to hold the charge controller and boost board.
   
![heat_set_inserts](https://github.com/user-attachments/assets/1a491290-beeb-4f9e-b3c7-51cbdd26d541)

4. **Install Power Switch**
   - In  the **bottom case**, slide the power switch into place. It should snap into the slot with a bit of firm pressure.
  
![power_switch](https://github.com/user-attachments/assets/fc600fc2-2d4e-4ed6-8dce-ed2539195530)

### Battery & Power Setup

1. **Prepare the Battery:**  
   - Fit your LiPo battery with a male JST connector, if not already present. This isn't required, but I highly recommend it. If you don't want to use JST connectors, you can use another appropriate connector, or solder the battery to the charge controller directly.
   - Solder a matching female JST connector onto the charge controller’s battery input terminals. Alternatively, solder the battery directly to the charge controller's battery input terminals. Note that the charge controller + boost converter used in this project is *always on*, so the variable voltage output terminals will be live whenever a power source is connected.

![battery_jst](https://github.com/user-attachments/assets/277de8ef-39ef-4a2a-9897-5b9c10d2d587)

2. **Adjust Voltage:**  
   - Connect the battery to the charge controller via the JST connector.
   - Use a multimeter to measure the voltage at the output terminals of the charge controller.
   - Adjust the onboard resistor until you reach a steady 5 volts.

  ![voltage](https://github.com/user-attachments/assets/3491084c-960f-4543-be97-7acb362a6af6)

3. **Solder Output Wires:**  
   - Solder wires to the positive and negative output terminals on the charge controller. These will power the LED matrix and other electronics.
  
![power_connector](https://github.com/user-attachments/assets/84d0f1a6-2fe5-4266-9574-aadd5d542622)

### LED Matrix Preparation

1. **Prepare the LED Matrix:**  
   - Use the supplied 3-wire connectors to attach wires to the LED matrix.  
   - **Important:** Ensure the wires are connected to the correct pads: positive, negative, and the **data in** pad (not data out).

  ![matrix_wires](https://github.com/user-attachments/assets/9be4bf61-b291-44f3-b0af-82b38450ea02)

### Prepping the D1 Mini

1. **Prepare the D1 Mini:**  
   - Grab your D1 Mini.

2. **Soldering Wires to the D1 Mini:**  
   - Solder a wire to the **5V** pin (power).
   - Solder a wire to the **GND** pin (ground).
   - Solder a wire to the **D4** pin, which will serve as the data out line to control the LED matrix.
   
![d1_mini_wires](https://github.com/user-attachments/assets/efa48442-8176-472f-ab1d-27cb885e183b)

### Wiring & Final Assembly

1. **Connect All Wiring:**  
   - Refer to the wiring diagram below to connect the battery, charge controller, LED matrix, power switch, and D1 Mini.
   - Make sure all solder joints are secure and insulated with heat shrink tubing where necessary.

  ![circuit_image (1)](https://github.com/user-attachments/assets/a1453730-6482-458c-9307-6c6e9394a03b)

2. **Final Assembly:**  
   - Once all wiring is complete, connect the battery.
   - Screw the back of the case together using M2 screws to secure the entire assembly.
   - Install the 3D printed led grid holder, diffuser, and case cover

  ![assembly_done](https://github.com/user-attachments/assets/d54213eb-119b-44de-aaa7-d29423abcfb4)
  ![final_assembly_2](https://github.com/user-attachments/assets/ae0a09ac-87e9-4988-aa32-f0f4e9652bf1)

---

## Software Setup

### Installing WLED

1. **Overview:**  
   WLED is a powerful tool that lets you run a variety of cool animations on your LED matrix.

2. **Installation:**  
   - Download the WLED firmware and flash it onto your D1 Mini following the instructions in the [WLED documentation](https://github.com/Aircoookie/WLED).
   - Configure your WiFi settings as prompted.
   - Once flashed, your LED matrix is ready to display animations!

### Installing the Custom Arduino Code (Gmail Notifications)

1. **Overview:**  
   For a custom twist, I've written an Arduino sketch that displays a Gmail logo on your LED matrix whenever you receive a new email.

2. **Setup Instructions:**  
   - Open the Arduino IDE and download the arduino sketch from [GitHub](https://github.com/yourusername/yourrepository).
   - Open the provided Arduino sketch.
   - **Important:** Update the placeholder WiFi credentials with your own network details, as the code needs internet access to check your Gmail inbox. Update the email and password fields with your own information as well. If you use two factor authentication, you'll need to generate an application specific password for the password field.
   - Make sure the power switch on your display is **off** and connect the D1 Mini to your computer.
   - Select the correct board and port for your D1 Mini in the Arduino IDE.
   - Upload the sketch to your D1 Mini.

3. **Testing:**  
   - Once the code is uploaded, power cycle your device.
   - Send a test email to your Gmail account and watch for the Gmail logo to appear on your LED matrix!

---

## Customization Ideas

This project is designed to be a launchpad for your own creative implementations. Here are some ideas:
- **Custom Notifications:** Modify the Arduino sketch to display different icons or animations for various alerts (e.g., chat messages, calendar reminders, weather alerts).
- **Additional Controls:** Add buttons, encoders, or even a small screen to enhance interactivity, or turn the display into some sort of gaming device.
- **Advanced Animations:** Explore more complex WLED effects or integrate sensor data for dynamic displays.

---

## License

This project is open source and available under the [MIT License](LICENSE).

---

Happy building and happy hacking! If you have any questions or modifications, please feel free to open an issue or submit a pull request.

## ❤️ Support Me ❤️

If you liked this project, please consider checking out [my shop](https://ko-fi.com/tuxedomakes/shop) or [buying me a coffee ☕](https://ko-fi.com/tuxedomakes).
