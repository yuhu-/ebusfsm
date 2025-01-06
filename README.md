ebus provides c++ classes to communicate via eBUS.

The eBUS is a two-wire bus that operates at a speed of 2400 baud and is used in heating systems. 
The participants (max. 25 masters, 228 slaves) exchange messages (=telegrams) in a byte-oriented
protocol with byte-oriented arbitration. Implementation with standard UART (8 bits + start and stop bits)
and a CRC byte (generator polynomial: x8 + x7 + x4 + x3 + x + 1) for data protection.

On the bus, a message is sent or received as a sequence of characters. The two main classes of this 
library, **Sequence** (low-level) and **Telegram** (high-level), can store such a sequence or message.

The purpose of the **Sequence** class is to replace or insert special characters and calculate the CRC byte. 
The **Telegram** class can analyze, generate and evaluate these sequences according to the eBUS specification.

The **EbusHandler** has implemented routines for sending all types of telegrams and the option of collecting
statistical data about the eBUS system. To perform this task, the EbusHandler requires a serial bus device.
The processing of received telegrams and the arbitration procedure, which currently has to be ensured 
externally, are not yet supported. 

**Datatypes** offers various functions for decoding/encoding in accordance with the eBUS data types.


Among examples:
**EbusStack** offers the possibility to act as a fully-fledged eBUS participant. It has been implemented
as a PIMPL idiom and runs in its own thread.


Compilation requires CMake and a C++ compiler with C++14 support. 

**EbusStack** also requires ppoll and pthread support.


For bugs and missing features use github issue system.

The author can be contacted at roland.jax@liwest.at.
