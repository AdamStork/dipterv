/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.9.3 at Sun Jan 12 19:59:04 2020. */

#include "functional_test.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t i2cTest_fields[4] = {
    PB_FIELD(  1, UENUM   , REQUIRED, STATIC  , FIRST, i2cTest, direction, direction, 0),
    PB_FIELD(  2, UINT32  , REQUIRED, STATIC  , OTHER, i2cTest, regAddr, direction, 0),
    PB_FIELD(  3, UINT32  , OPTIONAL, STATIC  , OTHER, i2cTest, regData, regAddr, 0),
    PB_LAST_FIELD
};

const pb_field_t spiTest_fields[4] = {
    PB_FIELD(  1, UENUM   , REQUIRED, STATIC  , FIRST, spiTest, direction, direction, 0),
    PB_FIELD(  2, UINT32  , OPTIONAL, STATIC  , OTHER, spiTest, regData, direction, 0),
    PB_FIELD(  3, UINT32  , OPTIONAL, STATIC  , OTHER, spiTest, spiMode, regData, 0),
    PB_LAST_FIELD
};

const pb_field_t gpioTest_fields[4] = {
    PB_FIELD(  1, UENUM   , REQUIRED, STATIC  , FIRST, gpioTest, pin, pin, 0),
    PB_FIELD(  2, UENUM   , REQUIRED, STATIC  , OTHER, gpioTest, direction, pin, 0),
    PB_FIELD(  3, UENUM   , REQUIRED, STATIC  , OTHER, gpioTest, pinState, direction, 0),
    PB_LAST_FIELD
};

const pb_field_t timerTest_fields[3] = {
    PB_FIELD(  1, UENUM   , REQUIRED, STATIC  , FIRST, timerTest, direction, direction, 0),
    PB_FIELD(  2, UENUM   , REQUIRED, STATIC  , OTHER, timerTest, pinState, direction, 0),
    PB_LAST_FIELD
};

const pb_field_t pwmTest_fields[4] = {
    PB_FIELD(  1, UENUM   , REQUIRED, STATIC  , FIRST, pwmTest, pin, pin, 0),
    PB_FIELD(  2, UINT32  , REQUIRED, STATIC  , OTHER, pwmTest, frequency, pin, 0),
    PB_FIELD(  3, UINT32  , REQUIRED, STATIC  , OTHER, pwmTest, dutyCycle, frequency, 0),
    PB_LAST_FIELD
};

const pb_field_t ledTest_fields[6] = {
    PB_FIELD(  1, BOOL    , REQUIRED, STATIC  , FIRST, ledTest, ledState, ledState, 0),
    PB_FIELD(  2, UINT32  , OPTIONAL, STATIC  , OTHER, ledTest, gpioPort, ledState, 0),
    PB_FIELD(  3, UINT32  , OPTIONAL, STATIC  , OTHER, ledTest, gpioPin, gpioPort, 0),
    PB_FIELD(  4, UINT32  , OPTIONAL, STATIC  , OTHER, ledTest, blinkingFrequency, gpioPin, 0),
    PB_FIELD(  5, UINT32  , OPTIONAL, STATIC  , OTHER, ledTest, luminance, blinkingFrequency, 0),
    PB_LAST_FIELD
};

const pb_field_t Command_fields[8] = {
    PB_FIELD(  1, UENUM   , REQUIRED, STATIC  , FIRST, Command, commandType, commandType, 0),
    PB_FIELD(  2, MESSAGE , OPTIONAL, STATIC  , OTHER, Command, i2cTestType, commandType, &i2cTest_fields),
    PB_FIELD(  3, MESSAGE , OPTIONAL, STATIC  , OTHER, Command, spiTestType, i2cTestType, &spiTest_fields),
    PB_FIELD(  5, MESSAGE , OPTIONAL, STATIC  , OTHER, Command, gpioTestType, spiTestType, &gpioTest_fields),
    PB_FIELD(  6, MESSAGE , OPTIONAL, STATIC  , OTHER, Command, timerTestType, gpioTestType, &timerTest_fields),
    PB_FIELD(  7, MESSAGE , OPTIONAL, STATIC  , OTHER, Command, pwmTestType, timerTestType, &pwmTest_fields),
    PB_FIELD( 10, MESSAGE , OPTIONAL, STATIC  , OTHER, Command, ledTesType, pwmTestType, &ledTest_fields),
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
PB_STATIC_ASSERT((pb_membersize(Command, i2cTestType) < 65536 && pb_membersize(Command, spiTestType) < 65536 && pb_membersize(Command, gpioTestType) < 65536 && pb_membersize(Command, timerTestType) < 65536 && pb_membersize(Command, pwmTestType) < 65536 && pb_membersize(Command, ledTesType) < 65536), YOU_MUST_DEFINE_PB_FIELD_32BIT_FOR_MESSAGES_i2cTest_spiTest_gpioTest_timerTest_pwmTest_ledTest_Command)
#endif

#if !defined(PB_FIELD_16BIT) && !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_16BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in the default
 * 8 bit descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(Command, i2cTestType) < 256 && pb_membersize(Command, spiTestType) < 256 && pb_membersize(Command, gpioTestType) < 256 && pb_membersize(Command, timerTestType) < 256 && pb_membersize(Command, pwmTestType) < 256 && pb_membersize(Command, ledTesType) < 256), YOU_MUST_DEFINE_PB_FIELD_16BIT_FOR_MESSAGES_i2cTest_spiTest_gpioTest_timerTest_pwmTest_ledTest_Command)
#endif


/* @@protoc_insertion_point(eof) */
