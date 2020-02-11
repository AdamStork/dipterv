/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.9.3 at Tue Feb 11 19:27:08 2020. */

#include "functional_test.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t i2cMessage_fields[8] = {
    PB_FIELD(  1, UENUM   , REQUIRED, STATIC  , FIRST, i2cMessage, bus, bus, 0),
    PB_FIELD(  2, UINT32  , REQUIRED, STATIC  , OTHER, i2cMessage, address, bus, 0),
    PB_FIELD(  3, UINT32  , REQUIRED, STATIC  , OTHER, i2cMessage, register, address, 0),
    PB_FIELD(  4, UENUM   , REQUIRED, STATIC  , OTHER, i2cMessage, direction, register, 0),
    PB_FIELD(  5, UENUM   , REQUIRED, STATIC  , OTHER, i2cMessage, speedMode, direction, 0),
    PB_FIELD(  6, UINT32  , REQUIRED, STATIC  , OTHER, i2cMessage, clockSpeed, speedMode, 0),
    PB_FIELD(  7, UENUM   , OPTIONAL, STATIC  , OTHER, i2cMessage, dutyCycle, clockSpeed, 0),
    PB_LAST_FIELD
};

const pb_field_t spiMessage_fields[10] = {
    PB_FIELD(  1, UENUM   , REQUIRED, STATIC  , FIRST, spiMessage, bus, bus, 0),
    PB_FIELD(  2, UINT32  , REQUIRED, STATIC  , OTHER, spiMessage, command, bus, 0),
    PB_FIELD(  3, UINT32  , REQUIRED, STATIC  , OTHER, spiMessage, dummyclocks, command, 0),
    PB_FIELD(  4, UENUM   , REQUIRED, STATIC  , OTHER, spiMessage, operatingMode, dummyclocks, 0),
    PB_FIELD(  5, UENUM   , REQUIRED, STATIC  , OTHER, spiMessage, hardwareNSS, operatingMode, 0),
    PB_FIELD(  6, UENUM   , REQUIRED, STATIC  , OTHER, spiMessage, frameFormat, hardwareNSS, 0),
    PB_FIELD(  7, UENUM   , REQUIRED, STATIC  , OTHER, spiMessage, dataSize, frameFormat, 0),
    PB_FIELD(  8, UENUM   , OPTIONAL, STATIC  , OTHER, spiMessage, firstBit, dataSize, 0),
    PB_FIELD(  9, UENUM   , OPTIONAL, STATIC  , OTHER, spiMessage, clockMode, firstBit, 0),
    PB_LAST_FIELD
};

const pb_field_t digitalGPIO_fields[5] = {
    PB_FIELD(  1, UENUM   , REQUIRED, STATIC  , FIRST, digitalGPIO, pin, pin, 0),
    PB_FIELD(  2, UENUM   , REQUIRED, STATIC  , OTHER, digitalGPIO, direction, pin, 0),
    PB_FIELD(  3, UENUM   , REQUIRED, STATIC  , OTHER, digitalGPIO, state, direction, 0),
    PB_FIELD(  4, UENUM   , REQUIRED, STATIC  , OTHER, digitalGPIO, pull, state, 0),
    PB_LAST_FIELD
};

const pb_field_t analogIN_fields[5] = {
    PB_FIELD(  1, UENUM   , REQUIRED, STATIC  , FIRST, analogIN, instance, instance, 0),
    PB_FIELD(  2, UENUM   , REQUIRED, STATIC  , OTHER, analogIN, pin, instance, 0),
    PB_FIELD(  3, UENUM   , REQUIRED, STATIC  , OTHER, analogIN, resolution, pin, 0),
    PB_FIELD(  4, UENUM   , REQUIRED, STATIC  , OTHER, analogIN, clockPrescaler, resolution, 0),
    PB_LAST_FIELD
};

const pb_field_t analogOUT_fields[6] = {
    PB_FIELD(  1, UENUM   , REQUIRED, STATIC  , FIRST, analogOUT, pin, pin, 0),
    PB_FIELD(  2, UINT32  , REQUIRED, STATIC  , OTHER, analogOUT, frequency, pin, 0),
    PB_FIELD(  3, UINT32  , REQUIRED, STATIC  , OTHER, analogOUT, dutyCycle, frequency, 0),
    PB_FIELD(  4, UENUM   , REQUIRED, STATIC  , OTHER, analogOUT, dependency, dutyCycle, 0),
    PB_FIELD(  5, UINT32  , OPTIONAL, STATIC  , OTHER, analogOUT, time, dependency, 0),
    PB_LAST_FIELD
};

const pb_field_t usartMessage_fields[13] = {
    PB_FIELD(  1, UENUM   , REQUIRED, STATIC  , FIRST, usartMessage, bus, bus, 0),
    PB_FIELD(  2, UENUM   , REQUIRED, STATIC  , OTHER, usartMessage, mode, bus, 0),
    PB_FIELD(  3, UINT32  , REQUIRED, STATIC  , OTHER, usartMessage, baudRate, mode, 0),
    PB_FIELD(  4, UENUM   , REQUIRED, STATIC  , OTHER, usartMessage, wordLength, baudRate, 0),
    PB_FIELD(  5, UENUM   , REQUIRED, STATIC  , OTHER, usartMessage, parity, wordLength, 0),
    PB_FIELD(  6, UENUM   , REQUIRED, STATIC  , OTHER, usartMessage, stopBits, parity, 0),
    PB_FIELD(  7, UENUM   , REQUIRED, STATIC  , OTHER, usartMessage, direction, stopBits, 0),
    PB_FIELD(  8, UINT32  , REQUIRED, STATIC  , OTHER, usartMessage, command, direction, 0),
    PB_FIELD(  9, UENUM   , OPTIONAL, STATIC  , OTHER, usartMessage, clockPolarity, command, 0),
    PB_FIELD( 10, UENUM   , OPTIONAL, STATIC  , OTHER, usartMessage, clockPhase, clockPolarity, 0),
    PB_FIELD( 11, UENUM   , OPTIONAL, STATIC  , OTHER, usartMessage, clockLastBit, clockPhase, 0),
    PB_FIELD( 12, UENUM   , OPTIONAL, STATIC  , OTHER, usartMessage, hwFlowControl, clockLastBit, 0),
    PB_LAST_FIELD
};

const pb_field_t Command_fields[10] = {
    PB_FIELD(  1, UENUM   , REQUIRED, STATIC  , FIRST, Command, commandType, commandType, 0),
    PB_FIELD(  2, MESSAGE , OPTIONAL, STATIC  , OTHER, Command, i2c, commandType, &i2cMessage_fields),
    PB_FIELD(  3, MESSAGE , OPTIONAL, STATIC  , OTHER, Command, spi, i2c, &spiMessage_fields),
    PB_FIELD(  4, MESSAGE , OPTIONAL, STATIC  , OTHER, Command, usart, spi, &usartMessage_fields),
    PB_FIELD(  5, MESSAGE , OPTIONAL, STATIC  , OTHER, Command, gpio, usart, &digitalGPIO_fields),
    PB_FIELD(  6, MESSAGE , OPTIONAL, STATIC  , OTHER, Command, analog_in, gpio, &analogIN_fields),
    PB_FIELD(  7, MESSAGE , OPTIONAL, STATIC  , OTHER, Command, analog_out, analog_in, &analogOUT_fields),
    PB_FIELD( 10, UINT32  , OPTIONAL, STATIC  , OTHER, Command, responseRead, analog_out, 0),
    PB_FIELD( 11, UENUM   , OPTIONAL, STATIC  , OTHER, Command, responseWrite, responseRead, 0),
    PB_LAST_FIELD
};

































/* Check that field information fits in pb_field_t */
#if !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_32BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in 8 or 16 bit
 * field descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(Command, i2c) < 65536 && pb_membersize(Command, spi) < 65536 && pb_membersize(Command, usart) < 65536 && pb_membersize(Command, gpio) < 65536 && pb_membersize(Command, analog_in) < 65536 && pb_membersize(Command, analog_out) < 65536), YOU_MUST_DEFINE_PB_FIELD_32BIT_FOR_MESSAGES_i2cMessage_spiMessage_digitalGPIO_analogIN_analogOUT_usartMessage_Command)
#endif

#if !defined(PB_FIELD_16BIT) && !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_16BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in the default
 * 8 bit descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(Command, i2c) < 256 && pb_membersize(Command, spi) < 256 && pb_membersize(Command, usart) < 256 && pb_membersize(Command, gpio) < 256 && pb_membersize(Command, analog_in) < 256 && pb_membersize(Command, analog_out) < 256), YOU_MUST_DEFINE_PB_FIELD_16BIT_FOR_MESSAGES_i2cMessage_spiMessage_digitalGPIO_analogIN_analogOUT_usartMessage_Command)
#endif


/* @@protoc_insertion_point(eof) */
