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
- Signaling error(ERR LED) PA3 -> A2
- Signaling transmit status(if transmit was successfull, TRANSMIT LED) PA4 -> A3
- Signaling receive status(if receive was successfull, RECEIVE LED) PA5 -> A4
- Signaling correct data(DATA LED) PA6 -> A5
