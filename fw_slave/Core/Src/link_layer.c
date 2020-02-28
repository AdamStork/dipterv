#include "link_layer.h"
#include <string.h>

void buffer_write(link_layer_t *handler, uint8_t byte);
void buffer_reset(link_layer_t *handler);

/*************************** RECEIVE ******************************/
/** @brief Resets receive buffer state variables**/
void buffer_reset(link_layer_t *handler)
{
    handler->frame_ready = 0;
    handler->receive_buffer_index = 0;
    handler->tx_buffer_size = 0;
}

/** @brief Add one byte to receive buffer **/
void buffer_write(link_layer_t *handler, uint8_t byte)
{
    handler->receive_buffer[handler->receive_buffer_index] = byte;
    ++(handler->receive_buffer_index);
}

/**  @brief Analyze incoming frame byte-by-byte and signals, if data field is ready for analyzing
 *	 @param handler: pointer to link layer handler
 *	 @param byte: received byte
 *	 **/
void link_parse_byte(link_layer_t *handler, uint8_t byte)
{
		switch	(handler->state){
			// if we are between two frames
			case WAIT_HEADER:
					if (BYTE_START == byte){ // only change if it's a start byte
						handler->state = IN_MSG;
						buffer_reset(handler);
					}
					else{ // if it's other type, stay in current state 
					}
					break;
			// if we are in a frame
			case IN_MSG:
					if (BYTE_START == byte){ // throw current frame, start a new
						buffer_reset(handler);
						// stay in IN_MSG
					}
					else if (BYTE_ESC == byte){ // change to AFTER_ESC
						handler->state = AFTER_ESC;
					}
					else if (BYTE_END == byte){ // end of frame
						handler->frame_ready = 1;
						handler->state = WAIT_HEADER;
					}
					else{	// byte is a normal data
						buffer_write(handler, byte);
						// stay in IN_MSG
					}
					break;
            // if the previous byte was an escape        
			case AFTER_ESC:
					buffer_write(handler, byte); // any byte is valid
					handler->state = IN_MSG;
					break;
		}
}

/** @brief Copy message to given buffer if parsing was successful
 * @param	frame: pointer to buffer to copy the message to
 * @param	length: buffer length is given with a pointer**/
bool link_get_valid_frame(link_layer_t *handler, uint8_t *frame, uint8_t *length)
{
    bool is_frame_ready = (bool)handler->frame_ready;
    if (is_frame_ready) {
        (*length) = handler->receive_buffer_index;
        memcpy(frame, handler->receive_buffer, (*length));
        handler->frame_ready = 0;
    }
    return is_frame_ready;
}




/*********************************** TRANSMIT **********************************/
/**@brief 	Frames and sends the data made with protocol buffer
 * @details An ESC character is included if data contains START, END or ESC
 * @param 	handler: pointer to link layer handler
 * @param	data: pointer to protocol buffer data field, which will be framed
 * @param	length: length of protocol buffer data field
 * **/
void link_write(link_layer_t *handler, uint8_t *data, uint8_t length)
{
    uint8_t tx_buffer_i = 0;

    handler->tx_buffer[tx_buffer_i] = BYTE_START;
    ++tx_buffer_i;

    for (uint8_t i = 0; i < length; ++i) {
        switch (data[i]) {
            case BYTE_START:
            case BYTE_END:
            case BYTE_ESC:
                handler->tx_buffer[tx_buffer_i] = BYTE_ESC;
                ++tx_buffer_i;
                break;

            default:
                break;
        }
        handler->tx_buffer[tx_buffer_i] = data[i];
        ++tx_buffer_i;
    }

    handler->tx_buffer[tx_buffer_i] = BYTE_END;
    ++tx_buffer_i;

    // Send the message to the physical layer
    handler->tx_buffer_size = tx_buffer_i;
}
