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


