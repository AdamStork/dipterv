/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.9.3 at Thu Feb 27 14:40:20 2020. */

#ifndef PB_SIMPLE_MESSAGE_PB_H_INCLUDED
#define PB_SIMPLE_MESSAGE_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _SimpleMessage {
    uint32_t msg;
/* @@protoc_insertion_point(struct:SimpleMessage) */
} SimpleMessage;

/* Default values for struct fields */

/* Initializer values for message structs */
#define SimpleMessage_init_default               {0}
#define SimpleMessage_init_zero                  {0}

/* Field tags (for use in manual encoding/decoding) */
#define SimpleMessage_msg_tag                    1

/* Struct field encoding specification for nanopb */
extern const pb_field_t SimpleMessage_fields[2];

/* Maximum encoded size of messages (where known) */
#define SimpleMessage_size                       6

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define SIMPLE_MESSAGE_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif