/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.9.3 at Sat Oct 19 22:52:29 2019. */

#ifndef PB_SENSOR_PB_H_INCLUDED
#define PB_SENSOR_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _SensorDataEnum {
    SensorDataEnum_SENSOR_ACCELEROMETER = 0,
    SensorDataEnum_SENSOR_TEMPERATURE = 1,
    SensorDataEnum_SENSOR_BATTERY = 2,
    SensorDataEnum_SENSOR_ECG = 3
} SensorDataEnum;
#define _SensorDataEnum_MIN SensorDataEnum_SENSOR_ACCELEROMETER
#define _SensorDataEnum_MAX SensorDataEnum_SENSOR_ECG
#define _SensorDataEnum_ARRAYSIZE ((SensorDataEnum)(SensorDataEnum_SENSOR_ECG+1))

typedef enum _CommandTypeEnum {
    CommandTypeEnum_SET_ENABLE_ACCELEROMETER = 0,
    CommandTypeEnum_SET_ENABLE_TEMP_SENSOR = 1,
    CommandTypeEnum_GET_TEMPERATURE_DATA = 2
} CommandTypeEnum;
#define _CommandTypeEnum_MIN CommandTypeEnum_SET_ENABLE_ACCELEROMETER
#define _CommandTypeEnum_MAX CommandTypeEnum_GET_TEMPERATURE_DATA
#define _CommandTypeEnum_ARRAYSIZE ((CommandTypeEnum)(CommandTypeEnum_GET_TEMPERATURE_DATA+1))

/* Struct definitions */
typedef struct _Command {
    CommandTypeEnum commandType;
    bool has_commandValue;
    int64_t commandValue;
/* @@protoc_insertion_point(struct:Command) */
} Command;

typedef struct _SensorDataArray_SensorData {
    SensorDataEnum sensorType;
    float value;
    int64_t timeStamp;
/* @@protoc_insertion_point(struct:SensorDataArray_SensorData) */
} SensorDataArray_SensorData;

typedef struct _UART_msg {
    char cmd1[40];
    char cmd2[40];
/* @@protoc_insertion_point(struct:UART_msg) */
} UART_msg;

typedef struct _SensorDataArray {
    pb_size_t array_count;
    SensorDataArray_SensorData array[10];
/* @@protoc_insertion_point(struct:SensorDataArray) */
} SensorDataArray;

/* Default values for struct fields */

/* Initializer values for message structs */
#define SensorDataArray_init_default             {0, {SensorDataArray_SensorData_init_default, SensorDataArray_SensorData_init_default, SensorDataArray_SensorData_init_default, SensorDataArray_SensorData_init_default, SensorDataArray_SensorData_init_default, SensorDataArray_SensorData_init_default, SensorDataArray_SensorData_init_default, SensorDataArray_SensorData_init_default, SensorDataArray_SensorData_init_default, SensorDataArray_SensorData_init_default}}
#define SensorDataArray_SensorData_init_default  {_SensorDataEnum_MIN, 0, 0}
#define Command_init_default                     {_CommandTypeEnum_MIN, false, 0}
#define UART_msg_init_default                    {"", ""}
#define SensorDataArray_init_zero                {0, {SensorDataArray_SensorData_init_zero, SensorDataArray_SensorData_init_zero, SensorDataArray_SensorData_init_zero, SensorDataArray_SensorData_init_zero, SensorDataArray_SensorData_init_zero, SensorDataArray_SensorData_init_zero, SensorDataArray_SensorData_init_zero, SensorDataArray_SensorData_init_zero, SensorDataArray_SensorData_init_zero, SensorDataArray_SensorData_init_zero}}
#define SensorDataArray_SensorData_init_zero     {_SensorDataEnum_MIN, 0, 0}
#define Command_init_zero                        {_CommandTypeEnum_MIN, false, 0}
#define UART_msg_init_zero                       {"", ""}

/* Field tags (for use in manual encoding/decoding) */
#define Command_commandType_tag                  1
#define Command_commandValue_tag                 2
#define SensorDataArray_SensorData_sensorType_tag 1
#define SensorDataArray_SensorData_value_tag     2
#define SensorDataArray_SensorData_timeStamp_tag 3
#define UART_msg_cmd1_tag                        1
#define UART_msg_cmd2_tag                        2
#define SensorDataArray_array_tag                1

/* Struct field encoding specification for nanopb */
extern const pb_field_t SensorDataArray_fields[2];
extern const pb_field_t SensorDataArray_SensorData_fields[4];
extern const pb_field_t Command_fields[3];
extern const pb_field_t UART_msg_fields[3];

/* Maximum encoded size of messages (where known) */
#define SensorDataArray_size                     200
#define SensorDataArray_SensorData_size          18
#define Command_size                             13
#define UART_msg_size                            84

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define SENSOR_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
