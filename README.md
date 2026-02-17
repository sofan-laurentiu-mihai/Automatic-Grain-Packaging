# Automatic-Grain-Packaging 🌽
Welcome to the **Automatic Grain Packaging** project. This system is designed for the transfer of grain from silos into trucks using industrial-grade PLC technology.
## Description 📖
Upon initializing the system, the automation manages the flow of grain to minimize human error and optimize loading times.
## System components ⚙️
The hardware setup is integrated into a proffesional industrial control panel, consisting of four key components:
* **Ultrasonic Sensor & Arduino Uno:** Monitors the container's capacity level and prevents the system from starting if the container is empty.
* **Push Button:** It's the operator's confirmation button. Verifies if a truck or container is in the correct position.
* **Solenoid:** The primary actuator that opens and closes the grain discharge valve.
* **Limit Switch:** Provides mechanical feedback to verify that the valve or solenoid has moved to the correct position.
## Logic Flow 🔃
The process follows a strict sequential logic to maintain operational safety:
1. **System Initialization:** The system powers on and initializes the control unit.
2. **Level Check:** The ultrasonic sensor monitors the grain levels and triggers a status LED.
3. **Actuation:** The solenoid is energized, opening the valve for loading.
4. **Feedback Verification:** After energizing, the system checks the Limit Switch to confirm succesfull mechanical movement.
# Features 🌟
* **Automated safety:** Prevents the runs in which the silo is empty.
* **Real-time Feedback:** Uses limit switches to ensure the hardware actually responds to software commands.
* **Industrial Reliability:** Built on the **Arduino Opta** platform for robust, long-term performance.
* **User-friendly Interface:** Simple manual start-up with visual LED indicators
## Credits 🖋️
This is a technical group project focused on industrial automation and IoT integration
**Sofan Laurentiu-Mihai** - Hardware & Software Engineer
**Burja Irina** - Hardware & Software Engineer

**There is a short video presentation of our project at** https://youtube.com/shorts/bvrgaChIbaI?feature=share
