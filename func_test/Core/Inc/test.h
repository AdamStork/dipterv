/*
 * test.h
 *
 *  Created on: 2019. okt. 19.
 *      Author: Golyszi
 */

#ifndef INC_TEST_H_
#define INC_TEST_H_
//#include <stdbool.h>
#include "functional_test.pb.h"

bool encode_message(uint8_t* pBuffer);
bool decode_message(uint8_t* pBuffer, Command* msg);

void buffer_init_zero(uint8_t* pBuffer, uint8_t pSize);

#endif /* INC_TEST_H_ */
