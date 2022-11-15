# Can repository for education purposes
Repository contains code for simple can networks that can have characteristics such as:
- Configurable baudrate:
  - 125 kbps(CAN_LOW_SPEED)
  - 250 kbps(CAN_HIGH_SPEED)
- Configurable type of microcontroller:
  - Receiver 
  - Transmitter
  - Receive and transmit
- Configurable mode of can
  - Loopback
  - Normal
- Configurable frames standard:
  - Standard(11 bit ID)
  - Extended(29 bit ID)

Can receiver and transmitter have 4 LEDs which are responsible for:
- Signaling error(ERR LED)
- Signaling transmit status(if transmit was successfull, TRANSMIT LED)
- Signaling receive status(if receive was successfull, RECEIVE LED)
- Signaling correct data(DATA LED)
