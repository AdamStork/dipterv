/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.9.3 at Fri Feb 21 19:56:16 2020. */

#ifndef PB_FUNCTIONAL_TEST_PB_H_INCLUDED
#define PB_FUNCTIONAL_TEST_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _CommandTypeEnum {
    CommandTypeEnum_LED_test = 0,
    CommandTypeEnum_I2C_test = 1,
    CommandTypeEnum_SPI_test = 2,
    CommandTypeEnum_USART_test = 3,
    CommandTypeEnum_GPIO_digital = 4,
    CommandTypeEnum_Analog_read = 5,
    CommandTypeEnum_Analog_write = 6
} CommandTypeEnum;
#define _CommandTypeEnum_MIN CommandTypeEnum_LED_test
#define _CommandTypeEnum_MAX CommandTypeEnum_Analog_write
#define _CommandTypeEnum_ARRAYSIZE ((CommandTypeEnum)(CommandTypeEnum_Analog_write+1))

typedef enum _i2cDirection {
    i2cDirection_I2C_write = 0,
    i2cDirection_I2C_read = 1
} i2cDirection;
#define _i2cDirection_MIN i2cDirection_I2C_write
#define _i2cDirection_MAX i2cDirection_I2C_read
#define _i2cDirection_ARRAYSIZE ((i2cDirection)(i2cDirection_I2C_read+1))

typedef enum _i2cBus {
    i2cBus_I2C1 = 1,
    i2cBus_I2C2 = 2,
    i2cBus_I2C3 = 3
} i2cBus;
#define _i2cBus_MIN i2cBus_I2C1
#define _i2cBus_MAX i2cBus_I2C3
#define _i2cBus_ARRAYSIZE ((i2cBus)(i2cBus_I2C3+1))

typedef enum _i2cSpeedMode {
    i2cSpeedMode_I2C_SPEED_MODE_STANDARD = 0,
    i2cSpeedMode_I2C_SPEED_MODE_FAST = 1
} i2cSpeedMode;
#define _i2cSpeedMode_MIN i2cSpeedMode_I2C_SPEED_MODE_STANDARD
#define _i2cSpeedMode_MAX i2cSpeedMode_I2C_SPEED_MODE_FAST
#define _i2cSpeedMode_ARRAYSIZE ((i2cSpeedMode)(i2cSpeedMode_I2C_SPEED_MODE_FAST+1))

typedef enum _i2cFastModeDutyCycle {
    i2cFastModeDutyCycle_I2C_DUTY_CYCLE_TLOW_THIGH_2 = 0,
    i2cFastModeDutyCycle_I2C_DUTY_CYCLE_TLOW_THIGH_16_9 = 1
} i2cFastModeDutyCycle;
#define _i2cFastModeDutyCycle_MIN i2cFastModeDutyCycle_I2C_DUTY_CYCLE_TLOW_THIGH_2
#define _i2cFastModeDutyCycle_MAX i2cFastModeDutyCycle_I2C_DUTY_CYCLE_TLOW_THIGH_16_9
#define _i2cFastModeDutyCycle_ARRAYSIZE ((i2cFastModeDutyCycle)(i2cFastModeDutyCycle_I2C_DUTY_CYCLE_TLOW_THIGH_16_9+1))

typedef enum _clockMode {
    clockMode_SPI_MODE_0 = 0,
    clockMode_SPI_MODE_1 = 1,
    clockMode_SPI_MODE_2 = 2,
    clockMode_SPI_MODE_3 = 3
} clockMode;
#define _clockMode_MIN clockMode_SPI_MODE_0
#define _clockMode_MAX clockMode_SPI_MODE_3
#define _clockMode_ARRAYSIZE ((clockMode)(clockMode_SPI_MODE_3+1))

typedef enum _spiHardwareNSS {
    spiHardwareNSS_DISABLE = 0,
    spiHardwareNSS_NSS_INPUT = 1,
    spiHardwareNSS_NSS_OUTPUT = 2
} spiHardwareNSS;
#define _spiHardwareNSS_MIN spiHardwareNSS_DISABLE
#define _spiHardwareNSS_MAX spiHardwareNSS_NSS_OUTPUT
#define _spiHardwareNSS_ARRAYSIZE ((spiHardwareNSS)(spiHardwareNSS_NSS_OUTPUT+1))

typedef enum _spiBus {
    spiBus_SPI1 = 1,
    spiBus_SPI2 = 2,
    spiBus_SPI3 = 3
} spiBus;
#define _spiBus_MIN spiBus_SPI1
#define _spiBus_MAX spiBus_SPI3
#define _spiBus_ARRAYSIZE ((spiBus)(spiBus_SPI3+1))

typedef enum _spiOperatingMode {
    spiOperatingMode_SPI_MODE_FULL_DUPLEX_MASTER = 0,
    spiOperatingMode_SPI_MODE_HALF_DUPLEX_MASTER = 1,
    spiOperatingMode_SPI_MODE_TRANSMIT_ONLY_MASTER = 2
} spiOperatingMode;
#define _spiOperatingMode_MIN spiOperatingMode_SPI_MODE_FULL_DUPLEX_MASTER
#define _spiOperatingMode_MAX spiOperatingMode_SPI_MODE_TRANSMIT_ONLY_MASTER
#define _spiOperatingMode_ARRAYSIZE ((spiOperatingMode)(spiOperatingMode_SPI_MODE_TRANSMIT_ONLY_MASTER+1))

typedef enum _spiFrameFormat {
    spiFrameFormat_SPI_FRAME_FORMAT_MOTOROLA = 0,
    spiFrameFormat_SPI_FRAME_FORMAT_TI = 1
} spiFrameFormat;
#define _spiFrameFormat_MIN spiFrameFormat_SPI_FRAME_FORMAT_MOTOROLA
#define _spiFrameFormat_MAX spiFrameFormat_SPI_FRAME_FORMAT_TI
#define _spiFrameFormat_ARRAYSIZE ((spiFrameFormat)(spiFrameFormat_SPI_FRAME_FORMAT_TI+1))

typedef enum _spiDataSize {
    spiDataSize_SPI_DATA_SIZE_8_BITS = 0,
    spiDataSize_SPI_DATA_SIZE_16_BITS = 1
} spiDataSize;
#define _spiDataSize_MIN spiDataSize_SPI_DATA_SIZE_8_BITS
#define _spiDataSize_MAX spiDataSize_SPI_DATA_SIZE_16_BITS
#define _spiDataSize_ARRAYSIZE ((spiDataSize)(spiDataSize_SPI_DATA_SIZE_16_BITS+1))

typedef enum _spiFirstBit {
    spiFirstBit_SPI_FIRST_BIT_MSB = 0,
    spiFirstBit_SPI_FIRST_BIT_LSB = 1
} spiFirstBit;
#define _spiFirstBit_MIN spiFirstBit_SPI_FIRST_BIT_MSB
#define _spiFirstBit_MAX spiFirstBit_SPI_FIRST_BIT_LSB
#define _spiFirstBit_ARRAYSIZE ((spiFirstBit)(spiFirstBit_SPI_FIRST_BIT_LSB+1))

typedef enum _gpioDirection {
    gpioDirection_GPIO_OUTPUT = 0,
    gpioDirection_GPIO_INPUT = 1
} gpioDirection;
#define _gpioDirection_MIN gpioDirection_GPIO_OUTPUT
#define _gpioDirection_MAX gpioDirection_GPIO_INPUT
#define _gpioDirection_ARRAYSIZE ((gpioDirection)(gpioDirection_GPIO_INPUT+1))

typedef enum _gpioPinState {
    gpioPinState_GPIO_LOW = 0,
    gpioPinState_GPIO_HIGH = 1,
    gpioPinState_GPIO_NON_APPLICABLE = 2
} gpioPinState;
#define _gpioPinState_MIN gpioPinState_GPIO_LOW
#define _gpioPinState_MAX gpioPinState_GPIO_NON_APPLICABLE
#define _gpioPinState_ARRAYSIZE ((gpioPinState)(gpioPinState_GPIO_NON_APPLICABLE+1))

typedef enum _gpioPins {
    gpioPins_PA0 = 0,
    gpioPins_PA1 = 1,
    gpioPins_PA2 = 2,
    gpioPins_PA3 = 3,
    gpioPins_PA4 = 4,
    gpioPins_PA5 = 5,
    gpioPins_PA6 = 6,
    gpioPins_PA7 = 7,
    gpioPins_PA8 = 8,
    gpioPins_PA9 = 9,
    gpioPins_PA10 = 10,
    gpioPins_PA11 = 11,
    gpioPins_PA12 = 12,
    gpioPins_PA13 = 13,
    gpioPins_PA14 = 14,
    gpioPins_PA15 = 15,
    gpioPins_PB0 = 20,
    gpioPins_PB1 = 21,
    gpioPins_PB2 = 22,
    gpioPins_PB3 = 23,
    gpioPins_PB4 = 24,
    gpioPins_PB5 = 25,
    gpioPins_PB6 = 26,
    gpioPins_PB7 = 27,
    gpioPins_PB8 = 28,
    gpioPins_PB9 = 29,
    gpioPins_PB10 = 30,
    gpioPins_PB11 = 31,
    gpioPins_PB12 = 32,
    gpioPins_PB13 = 33,
    gpioPins_PB14 = 34,
    gpioPins_PB15 = 35,
    gpioPins_PC0 = 40,
    gpioPins_PC1 = 41,
    gpioPins_PC2 = 42,
    gpioPins_PC3 = 43,
    gpioPins_PC4 = 44,
    gpioPins_PC5 = 45,
    gpioPins_PC6 = 46,
    gpioPins_PC7 = 47,
    gpioPins_PC8 = 48,
    gpioPins_PC9 = 49,
    gpioPins_PC10 = 50,
    gpioPins_PC11 = 51,
    gpioPins_PC12 = 52,
    gpioPins_PC13 = 53,
    gpioPins_PC14 = 54,
    gpioPins_PC15 = 55,
    gpioPins_P_INVALID = 100
} gpioPins;
#define _gpioPins_MIN gpioPins_PA0
#define _gpioPins_MAX gpioPins_P_INVALID
#define _gpioPins_ARRAYSIZE ((gpioPins)(gpioPins_P_INVALID+1))

typedef enum _gpioPull {
    gpioPull_GPIO_NO_PULL = 0,
    gpioPull_GPIO_PULL_UP = 1,
    gpioPull_GPIO_PULL_DOWN = 2
} gpioPull;
#define _gpioPull_MIN gpioPull_GPIO_NO_PULL
#define _gpioPull_MAX gpioPull_GPIO_PULL_DOWN
#define _gpioPull_ARRAYSIZE ((gpioPull)(gpioPull_GPIO_PULL_DOWN+1))

typedef enum _adcInstance {
    adcInstance_ADC1 = 1,
    adcInstance_ADC2 = 2,
    adcInstance_ADC3 = 3
} adcInstance;
#define _adcInstance_MIN adcInstance_ADC1
#define _adcInstance_MAX adcInstance_ADC3
#define _adcInstance_ARRAYSIZE ((adcInstance)(adcInstance_ADC3+1))

typedef enum _adcResolution {
    adcResolution_ADC_12_BITS = 0,
    adcResolution_ADC_10_BITS = 1,
    adcResolution_ADC_8_BITS = 2,
    adcResolution_ADC_6_BITS = 3
} adcResolution;
#define _adcResolution_MIN adcResolution_ADC_12_BITS
#define _adcResolution_MAX adcResolution_ADC_6_BITS
#define _adcResolution_ARRAYSIZE ((adcResolution)(adcResolution_ADC_6_BITS+1))

typedef enum _adcClockPrescaler {
    adcClockPrescaler_ADC_PCLK2_DIVIDED_BY_4 = 0,
    adcClockPrescaler_ADC_PCLK2_DIVIDED_BY_6 = 1,
    adcClockPrescaler_ADC_PCLK2_DIVIDED_BY_8 = 2
} adcClockPrescaler;
#define _adcClockPrescaler_MIN adcClockPrescaler_ADC_PCLK2_DIVIDED_BY_4
#define _adcClockPrescaler_MAX adcClockPrescaler_ADC_PCLK2_DIVIDED_BY_8
#define _adcClockPrescaler_ARRAYSIZE ((adcClockPrescaler)(adcClockPrescaler_ADC_PCLK2_DIVIDED_BY_8+1))

typedef enum _adcChannel {
    adcChannel_ADC_CHANNEL_IN0 = 0,
    adcChannel_ADC_CHANNEL_IN1 = 1,
    adcChannel_ADC_CHANNEL_IN2 = 2,
    adcChannel_ADC_CHANNEL_IN3 = 3,
    adcChannel_ADC_CHANNEL_IN4 = 4,
    adcChannel_ADC_CHANNEL_IN5 = 5,
    adcChannel_ADC_CHANNEL_IN6 = 6,
    adcChannel_ADC_CHANNEL_IN7 = 7,
    adcChannel_ADC_CHANNEL_IN8 = 8,
    adcChannel_ADC_CHANNEL_IN9 = 9,
    adcChannel_ADC_CHANNEL_IN10 = 10,
    adcChannel_ADC_CHANNEL_IN11 = 11,
    adcChannel_ADC_CHANNEL_IN12 = 12,
    adcChannel_ADC_CHANNEL_IN13 = 13,
    adcChannel_ADC_CHANNEL_IN14 = 14,
    adcChannel_ADC_CHANNEL_IN15 = 15,
    adcChannel_ADC_CHANNEL_TEMP = 20,
    adcChannel_ADC_CHANNEL_VREFINT = 21,
    adcChannel_ADC_CHANNEL_VBAT = 22
} adcChannel;
#define _adcChannel_MIN adcChannel_ADC_CHANNEL_IN0
#define _adcChannel_MAX adcChannel_ADC_CHANNEL_VBAT
#define _adcChannel_ARRAYSIZE ((adcChannel)(adcChannel_ADC_CHANNEL_VBAT+1))

typedef enum _pwmTimeDependency {
    pwmTimeDependency_PWM_TIME_DEPENDENCY_DISABLED = 0,
    pwmTimeDependency_PWM_TIME_DEPENDENCY_ENABLED = 1
} pwmTimeDependency;
#define _pwmTimeDependency_MIN pwmTimeDependency_PWM_TIME_DEPENDENCY_DISABLED
#define _pwmTimeDependency_MAX pwmTimeDependency_PWM_TIME_DEPENDENCY_ENABLED
#define _pwmTimeDependency_ARRAYSIZE ((pwmTimeDependency)(pwmTimeDependency_PWM_TIME_DEPENDENCY_ENABLED+1))

typedef enum _usartBus {
    usartBus_USART1 = 1,
    usartBus_USART2 = 2,
    usartBus_USART3 = 3,
    usartBus_USART4 = 4,
    usartBus_USART5 = 5,
    usartBus_USART6 = 6
} usartBus;
#define _usartBus_MIN usartBus_USART1
#define _usartBus_MAX usartBus_USART6
#define _usartBus_ARRAYSIZE ((usartBus)(usartBus_USART6+1))

typedef enum _usartDirection {
    usartDirection_USART_TX = 0,
    usartDirection_USART_TX_AND_RX = 1
} usartDirection;
#define _usartDirection_MIN usartDirection_USART_TX
#define _usartDirection_MAX usartDirection_USART_TX_AND_RX
#define _usartDirection_ARRAYSIZE ((usartDirection)(usartDirection_USART_TX_AND_RX+1))

typedef enum _usartWordLength {
    usartWordLength_USART_8_BITS = 0,
    usartWordLength_USART_9_BITS = 1
} usartWordLength;
#define _usartWordLength_MIN usartWordLength_USART_8_BITS
#define _usartWordLength_MAX usartWordLength_USART_9_BITS
#define _usartWordLength_ARRAYSIZE ((usartWordLength)(usartWordLength_USART_9_BITS+1))

typedef enum _usartParity {
    usartParity_USART_PARITY_NONE = 0,
    usartParity_USART_PARITY_EVEN = 1,
    usartParity_USART_PARITY_ODD = 2
} usartParity;
#define _usartParity_MIN usartParity_USART_PARITY_NONE
#define _usartParity_MAX usartParity_USART_PARITY_ODD
#define _usartParity_ARRAYSIZE ((usartParity)(usartParity_USART_PARITY_ODD+1))

typedef enum _usartStopBits {
    usartStopBits_USART_STOP_BITS_1 = 1,
    usartStopBits_USART_STOP_BITS_2 = 2
} usartStopBits;
#define _usartStopBits_MIN usartStopBits_USART_STOP_BITS_1
#define _usartStopBits_MAX usartStopBits_USART_STOP_BITS_2
#define _usartStopBits_ARRAYSIZE ((usartStopBits)(usartStopBits_USART_STOP_BITS_2+1))

typedef enum _usartMode {
    usartMode_USART_MODE_ASYNCHRONOUS = 0,
    usartMode_USART_MODE_SYNCHRONOUS = 1
} usartMode;
#define _usartMode_MIN usartMode_USART_MODE_ASYNCHRONOUS
#define _usartMode_MAX usartMode_USART_MODE_SYNCHRONOUS
#define _usartMode_ARRAYSIZE ((usartMode)(usartMode_USART_MODE_SYNCHRONOUS+1))

typedef enum _usartHardwareFlowControl {
    usartHardwareFlowControl_USART_HW_FLOW_DISABLE = 0,
    usartHardwareFlowControl_USART_HW_FLOW_CTS_ONLY = 1,
    usartHardwareFlowControl_USART_HW_FLOW_RTS_ONLY = 2,
    usartHardwareFlowControl_USART_HW_FLOW_CTS_AND_RTS = 3
} usartHardwareFlowControl;
#define _usartHardwareFlowControl_MIN usartHardwareFlowControl_USART_HW_FLOW_DISABLE
#define _usartHardwareFlowControl_MAX usartHardwareFlowControl_USART_HW_FLOW_CTS_AND_RTS
#define _usartHardwareFlowControl_ARRAYSIZE ((usartHardwareFlowControl)(usartHardwareFlowControl_USART_HW_FLOW_CTS_AND_RTS+1))

typedef enum _usartClockPolarity {
    usartClockPolarity_USART_CLOCK_POLARITY_LOW = 0,
    usartClockPolarity_USART_CLOCK_POLARITY_HIGH = 1
} usartClockPolarity;
#define _usartClockPolarity_MIN usartClockPolarity_USART_CLOCK_POLARITY_LOW
#define _usartClockPolarity_MAX usartClockPolarity_USART_CLOCK_POLARITY_HIGH
#define _usartClockPolarity_ARRAYSIZE ((usartClockPolarity)(usartClockPolarity_USART_CLOCK_POLARITY_HIGH+1))

typedef enum _usartClockPhase {
    usartClockPhase_USART_CLOCK_PHASE_ONE_EDGE = 0,
    usartClockPhase_USART_CLOCK_PHASE_TWO_EDGE = 1
} usartClockPhase;
#define _usartClockPhase_MIN usartClockPhase_USART_CLOCK_PHASE_ONE_EDGE
#define _usartClockPhase_MAX usartClockPhase_USART_CLOCK_PHASE_TWO_EDGE
#define _usartClockPhase_ARRAYSIZE ((usartClockPhase)(usartClockPhase_USART_CLOCK_PHASE_TWO_EDGE+1))

typedef enum _usartClockLastBit {
    usartClockLastBit_USART_CLOCK_LAST_BIT_DISABLE = 0,
    usartClockLastBit_USART_CLOCK_LAST_BIT_ENABLE = 1
} usartClockLastBit;
#define _usartClockLastBit_MIN usartClockLastBit_USART_CLOCK_LAST_BIT_DISABLE
#define _usartClockLastBit_MAX usartClockLastBit_USART_CLOCK_LAST_BIT_ENABLE
#define _usartClockLastBit_ARRAYSIZE ((usartClockLastBit)(usartClockLastBit_USART_CLOCK_LAST_BIT_ENABLE+1))

typedef enum _responseEnum_t {
    responseEnum_t_I2C_WRITE_OK = 0,
    responseEnum_t_I2C_WRITE_FAIL = 1,
    responseEnum_t_I2C_READ_FAIL = 2,
    responseEnum_t_SPI_TRANSMISSION_OK = 3,
    responseEnum_t_SPI_TRANSMISSION_FAIL = 4,
    responseEnum_t_USART_TX_OK = 5,
    responseEnum_t_USART_TX_FAIL = 6,
    responseEnum_t_GPIO_SET_HIGH = 7,
    responseEnum_t_GPIO_SET_LOW = 8,
    responseEnum_t_GPIO_WRITE_FAIL = 9,
    responseEnum_t_PWM_SET = 10,
    responseEnum_t_PWM_RESET = 11,
    responseEnum_t_PWM_SET_FAIL = 12
} responseEnum_t;
#define _responseEnum_t_MIN responseEnum_t_I2C_WRITE_OK
#define _responseEnum_t_MAX responseEnum_t_PWM_SET_FAIL
#define _responseEnum_t_ARRAYSIZE ((responseEnum_t)(responseEnum_t_PWM_SET_FAIL+1))

/* Struct definitions */
typedef struct _analogIN {
    adcInstance instance;
    adcChannel channel;
    gpioPins pin;
    adcResolution resolution;
    adcClockPrescaler clockPrescaler;
/* @@protoc_insertion_point(struct:analogIN) */
} analogIN;

typedef struct _analogOUT {
    gpioPins pin;
    uint32_t frequency;
    uint32_t dutyCycle;
    pwmTimeDependency dependency;
    bool has_time;
    uint32_t time;
/* @@protoc_insertion_point(struct:analogOUT) */
} analogOUT;

typedef struct _digitalGPIO {
    gpioPins pin;
    gpioDirection direction;
    gpioPinState state;
    gpioPull pull;
/* @@protoc_insertion_point(struct:digitalGPIO) */
} digitalGPIO;

typedef struct _i2cMessage {
    i2cBus bus;
    uint32_t address;
    uint32_t reg;
    i2cDirection direction;
    i2cSpeedMode speedMode;
    uint32_t clockSpeed;
    bool has_dutyCycle;
    i2cFastModeDutyCycle dutyCycle;
    uint32_t size;
    bool has_writeValue;
    uint32_t writeValue;
/* @@protoc_insertion_point(struct:i2cMessage) */
} i2cMessage;

typedef struct _responseMessage {
    bool has_responseRead;
    uint32_t responseRead;
    bool has_responseEnum;
    responseEnum_t responseEnum;
/* @@protoc_insertion_point(struct:responseMessage) */
} responseMessage;

typedef struct _spiMessage {
    spiBus bus;
    uint32_t command;
    uint32_t dummyclocks;
    spiOperatingMode operatingMode;
    spiHardwareNSS hardwareNSS;
    spiFrameFormat frameFormat;
    spiDataSize dataSize;
    bool has_firstBit;
    spiFirstBit firstBit;
    bool has_clockMode;
    clockMode clockMode;
/* @@protoc_insertion_point(struct:spiMessage) */
} spiMessage;

typedef struct _usartMessage {
    usartBus bus;
    usartMode mode;
    uint32_t baudRate;
    usartWordLength wordLength;
    usartParity parity;
    usartStopBits stopBits;
    usartDirection direction;
    uint32_t command;
    bool has_clockPolarity;
    usartClockPolarity clockPolarity;
    bool has_clockPhase;
    usartClockPhase clockPhase;
    bool has_clockLastBit;
    usartClockLastBit clockLastBit;
    bool has_hwFlowControl;
    usartHardwareFlowControl hwFlowControl;
/* @@protoc_insertion_point(struct:usartMessage) */
} usartMessage;

typedef struct _Command {
    CommandTypeEnum commandType;
    bool has_i2c;
    i2cMessage i2c;
    bool has_spi;
    spiMessage spi;
    bool has_usart;
    usartMessage usart;
    bool has_gpio;
    digitalGPIO gpio;
    bool has_analog_in;
    analogIN analog_in;
    bool has_analog_out;
    analogOUT analog_out;
    bool has_response;
    responseMessage response;
    bool has_autoConfig;
    bool autoConfig;
/* @@protoc_insertion_point(struct:Command) */
} Command;

/* Default values for struct fields */

/* Initializer values for message structs */
#define i2cMessage_init_default                  {_i2cBus_MIN, 0, 0, _i2cDirection_MIN, _i2cSpeedMode_MIN, 0, false, _i2cFastModeDutyCycle_MIN, 0, false, 0}
#define spiMessage_init_default                  {_spiBus_MIN, 0, 0, _spiOperatingMode_MIN, _spiHardwareNSS_MIN, _spiFrameFormat_MIN, _spiDataSize_MIN, false, _spiFirstBit_MIN, false, _clockMode_MIN}
#define digitalGPIO_init_default                 {_gpioPins_MIN, _gpioDirection_MIN, _gpioPinState_MIN, _gpioPull_MIN}
#define analogIN_init_default                    {_adcInstance_MIN, _adcChannel_MIN, _gpioPins_MIN, _adcResolution_MIN, _adcClockPrescaler_MIN}
#define analogOUT_init_default                   {_gpioPins_MIN, 0, 0, _pwmTimeDependency_MIN, false, 0}
#define usartMessage_init_default                {_usartBus_MIN, _usartMode_MIN, 0, _usartWordLength_MIN, _usartParity_MIN, _usartStopBits_MIN, _usartDirection_MIN, 0, false, _usartClockPolarity_MIN, false, _usartClockPhase_MIN, false, _usartClockLastBit_MIN, false, _usartHardwareFlowControl_MIN}
#define responseMessage_init_default             {false, 0, false, _responseEnum_t_MIN}
#define Command_init_default                     {_CommandTypeEnum_MIN, false, i2cMessage_init_default, false, spiMessage_init_default, false, usartMessage_init_default, false, digitalGPIO_init_default, false, analogIN_init_default, false, analogOUT_init_default, false, responseMessage_init_default, false, 0}
#define i2cMessage_init_zero                     {_i2cBus_MIN, 0, 0, _i2cDirection_MIN, _i2cSpeedMode_MIN, 0, false, _i2cFastModeDutyCycle_MIN, 0, false, 0}
#define spiMessage_init_zero                     {_spiBus_MIN, 0, 0, _spiOperatingMode_MIN, _spiHardwareNSS_MIN, _spiFrameFormat_MIN, _spiDataSize_MIN, false, _spiFirstBit_MIN, false, _clockMode_MIN}
#define digitalGPIO_init_zero                    {_gpioPins_MIN, _gpioDirection_MIN, _gpioPinState_MIN, _gpioPull_MIN}
#define analogIN_init_zero                       {_adcInstance_MIN, _adcChannel_MIN, _gpioPins_MIN, _adcResolution_MIN, _adcClockPrescaler_MIN}
#define analogOUT_init_zero                      {_gpioPins_MIN, 0, 0, _pwmTimeDependency_MIN, false, 0}
#define usartMessage_init_zero                   {_usartBus_MIN, _usartMode_MIN, 0, _usartWordLength_MIN, _usartParity_MIN, _usartStopBits_MIN, _usartDirection_MIN, 0, false, _usartClockPolarity_MIN, false, _usartClockPhase_MIN, false, _usartClockLastBit_MIN, false, _usartHardwareFlowControl_MIN}
#define responseMessage_init_zero                {false, 0, false, _responseEnum_t_MIN}
#define Command_init_zero                        {_CommandTypeEnum_MIN, false, i2cMessage_init_zero, false, spiMessage_init_zero, false, usartMessage_init_zero, false, digitalGPIO_init_zero, false, analogIN_init_zero, false, analogOUT_init_zero, false, responseMessage_init_zero, false, 0}

/* Field tags (for use in manual encoding/decoding) */
#define analogIN_instance_tag                    1
#define analogIN_channel_tag                     2
#define analogIN_pin_tag                         3
#define analogIN_resolution_tag                  4
#define analogIN_clockPrescaler_tag              5
#define analogOUT_pin_tag                        1
#define analogOUT_frequency_tag                  2
#define analogOUT_dutyCycle_tag                  3
#define analogOUT_dependency_tag                 4
#define analogOUT_time_tag                       5
#define digitalGPIO_pin_tag                      1
#define digitalGPIO_direction_tag                2
#define digitalGPIO_state_tag                    3
#define digitalGPIO_pull_tag                     4
#define i2cMessage_bus_tag                       1
#define i2cMessage_address_tag                   2
#define i2cMessage_reg_tag                       3
#define i2cMessage_direction_tag                 4
#define i2cMessage_speedMode_tag                 5
#define i2cMessage_clockSpeed_tag                6
#define i2cMessage_dutyCycle_tag                 7
#define i2cMessage_size_tag                      8
#define i2cMessage_writeValue_tag                9
#define responseMessage_responseRead_tag         1
#define responseMessage_responseEnum_tag         2
#define spiMessage_bus_tag                       1
#define spiMessage_command_tag                   2
#define spiMessage_dummyclocks_tag               3
#define spiMessage_operatingMode_tag             4
#define spiMessage_hardwareNSS_tag               5
#define spiMessage_frameFormat_tag               6
#define spiMessage_dataSize_tag                  7
#define spiMessage_firstBit_tag                  8
#define spiMessage_clockMode_tag                 9
#define usartMessage_bus_tag                     1
#define usartMessage_mode_tag                    2
#define usartMessage_baudRate_tag                3
#define usartMessage_wordLength_tag              4
#define usartMessage_parity_tag                  5
#define usartMessage_stopBits_tag                6
#define usartMessage_direction_tag               7
#define usartMessage_command_tag                 8
#define usartMessage_clockPolarity_tag           9
#define usartMessage_clockPhase_tag              10
#define usartMessage_clockLastBit_tag            11
#define usartMessage_hwFlowControl_tag           12
#define Command_commandType_tag                  1
#define Command_i2c_tag                          2
#define Command_spi_tag                          3
#define Command_usart_tag                        4
#define Command_gpio_tag                         5
#define Command_analog_in_tag                    6
#define Command_analog_out_tag                   7
#define Command_response_tag                     10
#define Command_autoConfig_tag                   11

/* Struct field encoding specification for nanopb */
extern const pb_field_t i2cMessage_fields[10];
extern const pb_field_t spiMessage_fields[10];
extern const pb_field_t digitalGPIO_fields[5];
extern const pb_field_t analogIN_fields[6];
extern const pb_field_t analogOUT_fields[6];
extern const pb_field_t usartMessage_fields[13];
extern const pb_field_t responseMessage_fields[3];
extern const pb_field_t Command_fields[10];

/* Maximum encoded size of messages (where known) */
#define i2cMessage_size                          38
#define spiMessage_size                          26
#define digitalGPIO_size                         8
#define analogIN_size                            10
#define analogOUT_size                           22
#define usartMessage_size                        32
#define responseMessage_size                     8
#define Command_size                             162

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define FUNCTIONAL_TEST_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
