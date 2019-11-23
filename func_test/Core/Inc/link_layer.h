#ifndef _LINK_LAYER_H
#define _LINK_LAYER_H
#include <stdbool.h>
#include <stdint.h>
#include <signal.h>

#define MSG_LENGTH_MAX  255
#define BYTE_START      0x5A
#define BYTE_END        0xA5
#define BYTE_ESC        0x7E

// Unescaping state machine
typedef enum{
	WAIT_HEADER, // waiting for a start byte (we are between two frames)
	IN_MSG,			 // we are in a frame
	AFTER_ESC		 // any next character is valid
} UnEscapingState;

typedef struct link_layer
{
    uint8_t receive_buffer[MSG_LENGTH_MAX];
    uint8_t receive_buffer_index;
    uint8_t tx_buffer[MSG_LENGTH_MAX];
    volatile sig_atomic_t frame_ready;
    void (*write_phy) (uint8_t *data, uint8_t length);
    UnEscapingState state;

} link_layer_t;

void link_parse_byte(link_layer_t * handler, uint8_t byte);
bool link_get_valid_frame(link_layer_t *handler, uint8_t *frame, uint8_t *length);
void link_write(link_layer_t *handler, uint8_t *data, uint8_t length);
void link_set_phy_write_fn(link_layer_t *handler, void (*fn)(uint8_t *data, uint8_t length));

#endif /* _LINK_LAYER_H */
