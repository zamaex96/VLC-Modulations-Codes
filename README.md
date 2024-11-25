Software based Modulations such as MPPM, multi-level, PPM, and PWM for VLC communication.

### AVR Microcontroller MPPM Program 

#### Purpose:
The program controls an AVR microcontroller to generate specific patterns of MPPM on Port D and Port B, and manages serial communication for data transmission.

#### Components:
1. **Serial Communication Initialization (`serial_init`):**
   - Initializes UART communication on two different UART modules (UART0 and UART1) at 19200 bps.
   
2. **Timer Initialization (`Timer1_init`):**
   - Configures Timer1 to generate interrupts at regular intervals for timing purposes.

3. **ISR (`TIMER1_OVF_vect`):**
   - Interrupt Service Routine for Timer1 overflow, increments a counter (`cnt`).

4. **Data Transmission Functions:**
   - `transmit0` and `transmit1`: Transmit data over UART0 and UART1 respectively.
   - `Rxdata` and `Rxdata1`: Receive data over UART0 and UART1 respectively.

5. **Bitwise Manipulation Functions:**
   - `CHECKBIT`: Macro to check specific bits in a byte.

6. **Port Control Functions:**
   - `send_code_portD` and `send_code_portB`: Send specific data patterns to Port D and Port B respectively using bitwise operations.
   - `new_data_send`: Sends a new data pattern to Port D.
   - `end_break` and `end_breakB`: Control functions for timing delays and port state changes.

7. **Main Function (`main`):**
   - Initializes peripherals and interrupts.
   - Loops indefinitely, sending predefined data patterns to Port D, toggling an output pin on Port A, and managing timing through `end_break`.

#### Key Points:
- Utilizes Timer interrupts for precise timing operations.
- Implements UART for serial communication.
- Controls multiple ports for outputting specific bit patterns.
- Includes delay mechanisms using busy-wait loops (`cnt` variable).

#### Recommendations:
- Consider optimizing delay mechanisms to reduce busy-wait time.
- Ensure synchronization and error handling in serial communication.

### AVR Microcontroller Multi-level Program Summary

#### Purpose:
The program controls an AVR microcontroller to perform the following tasks:
- Initialize serial communication for UART0 and UART1.
- Initialize Timer1 for precise timing operations.
- Control output on Port C based on bit patterns.
- Receive sensor data over UART0.

#### Components:
1. **Serial Communication Initialization (`serial_init`):**
   - Sets baud rates for UART0 and UART1.
   - Configures UART settings for 8-bit data, no parity, 1 stop bit.

2. **Timer Initialization (`Timer1_init`):**
   - Configures Timer1 in Phase Correct PWM mode with a prescaler of 8.
   - Sets Timer1 to overflow at a specific cycle (`cycles`).

3. **ISR (`TIMER1_OVF_vect`):**
   - Interrupt Service Routine increments a volatile counter (`cnt`) on Timer1 overflow.

4. **Data Transmission Functions:**
   - `transmit0` and `transmit1`: Transmit data over UART0 and UART1 respectively.
   - `Rxdata`: Receive data over UART0.

5. **Port Control Function (`multilevel`):**
   - Controls Port C output based on the bit pattern of input data.
   - Uses busy-wait loops (`cnt`) for timing delays.

6. **Sensor Data Retrieval (`getSensorData`):**
   - Transmits a sequence of commands over UART0 to retrieve sensor data.
   - Stores received data in the array `data`.

7. **Main Function (`main`):**
   - Initializes peripherals and interrupts.
   - Sets Port A, C, and D as output ports.
   - Loops indefinitely, controlling Port C output based on predefined bit patterns and toggling an output pin on Port A.

#### Key Points:
- Utilizes UART for serial communication and Timer1 for timing applications.
- Implements busy-wait delay loops (`cnt`) for timing control.
- Configures multiple ports (A, C, D) for output operations.
- Integrates sensor data retrieval via UART communication.

#### Recommendations:
- Consider optimizing timing mechanisms to reduce reliance on busy-wait loops.
- Implement error handling and synchronization mechanisms for UART communication.
- Ensure consistent and efficient use of resources across all components.

### PPM

#### Purpose:
The program controls an AVR microcontroller to perform the following tasks:
- Initialize serial communication for UART0 and UART1.
- Initialize Timer1 for precise timing operations.
- Control output on Ports C, D, and F based on bit patterns.
- Toggle an output pin on Port A.

#### Components:
1. **Serial Communication Initialization (`serial_init`):**
   - Sets baud rates for UART0 and UART1.
   - Configures UART settings for 8-bit data, no parity, 1 stop bit.

2. **Timer Initialization (`Timer1_init`):**
   - Configures Timer1 in Phase Correct PWM mode with a prescaler of 8.
   - Sets Timer1 to overflow at a specific cycle (`cycles`).

3. **ISR (`TIMER1_OVF_vect`):**
   - Interrupt Service Routine increments a volatile counter (`cnt`) on Timer1 overflow.

4. **Data Transmission Functions:**
   - `transmit0` and `transmit1`: Transmit data over UART0 and UART1 respectively.
   - `Rxdata` and `Rxdata1`: Receive data over UART0 and UART1 respectively.

5. **Port Output Functions (`send_ppm_new_C` and `send_ppm_new_F`):**
   - Controls output on Ports C and F based on the bit pattern of input data.
   - Delays using a busy-wait loop (`cnt`) for timing control.

6. **Main Function (`main`):**
   - Initializes peripherals and interrupts.
   - Sets Ports A, C, D, and F as output ports.
   - Loops indefinitely, transmitting predefined bit patterns through Ports C and optionally F, toggling an output pin on Port A.

#### Key Points:
- Uses UART for serial communication and Timer1 for precise timing.
- Implements busy-wait delay loops (`cnt`) for timing control.
- Configures multiple ports (A, C, D, F) for output operations.
- Demonstrates the use of ISR for Timer1 overflow.

#### Recommendations:
- Consider optimizing timing mechanisms to reduce reliance on busy-wait loops.
- Ensure synchronization and error handling for UART communication.
- Validate and adjust timing settings (`cycles`) for specific application requirements.

### PWM Program Summary

#### Purpose:
The program controls an AVR microcontroller to perform the following tasks:
- Initialize serial communication for UART0 and UART1.
- Initialize Timer1 for precise timing operations.
- Control output on Ports A, B, D, C, and F based on bit patterns.
- Toggle an output pin on Port A.
- Read sensor data over UART0.

#### Components:
1. **Serial Communication Initialization (`serial_init`):**
   - Sets baud rates for UART0 and UART1.
   - Configures UART settings for 8-bit data, no parity, 1 stop bit.

2. **Timer Initialization (`Timer1_init`):**
   - Configures Timer1 in Phase Correct PWM mode with a prescaler of 8.
   - Sets Timer1 to overflow at a specific cycle (`cycles`).

3. **ISR (`TIMER1_OVF_vect`):**
   - Interrupt Service Routine increments a volatile counter (`cnt`) on Timer1 overflow.

4. **Data Transmission Functions:**
   - `transmit0` and `transmit1`: Transmit data over UART0 and UART1 respectively.
   - `Rxdata`: Receive data over UART0.

5. **PWM Control Functions (`pwm_test` and `pwm_test_B`):**
   - Generates PWM signals on Ports A and B based on the bit pattern of input data.
   - Delays using a busy-wait loop (`cnt`) for timing control.

6. **End Space Function (`end_space`):**
   - Generates an end space signal on Port A with a predefined sequence of pulses.

7. **Sensor Data Acquisition (`getSensorData`):**
   - Sends commands over UART0 to request sensor data and receives 32 bytes of data into an array (`data`).

8. **Main Function (`main`):**
   - Initializes peripherals and interrupts.
   - Sets Ports A, B, C, D, and F as output ports.
   - Loops indefinitely, generating PWM signals on Port A, reading sensor data, and toggling an output pin on Port A.

#### Key Points:
- Uses UART for serial communication and Timer1 for precise timing.
- Implements busy-wait delay loops (`cnt`) for timing control in PWM functions.
- Handles multiple output ports for PWM signal generation and end space signal.
- Demonstrates the use of ISR for Timer1 overflow and UART data reception.

#### Recommendations:
- Optimize timing mechanisms to reduce reliance on busy-wait loops.
- Ensure synchronization and error handling for UART communication, especially in `getSensorData`.
- Validate and adjust timing settings (`cycles`) and PWM patterns (`pwm_test` and `pwm_test_B`) based on specific application requirements.

<div align="center">
  <a href="https://maazsalman.org/">
    <img width="70" src="click-svgrepo-com.svg" alt="gh" />
  </a>
  <p> Explore More! 🚀</p>
</div>




