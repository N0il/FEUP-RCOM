#ifndef API_RECEIVER_H
#define API_RECEIVER_H

/**
 * @file api_receiver.h
 * @brief API llopen and llclose for receiver
 * @version 0.1
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include "macrosLD.h"

struct termios oldtio, newtio;

/**
 * @brief Verifies if the buf's bytes are equivalent to a SET
 * 
 * @param byte_recieved byte to be verified
 * @param idx index of the byte to be verified
 * 
 * @return 0 in case of error, 1 otherwise
 */
int checkSETByteRecieved(unsigned char byte_recieved, int idx);

/**
 * @brief Verifies if the buf's bytes are equivalent to a DISC sent by the transmitter
 * 
 * @param byte_recieved byte to be verified
 * @param idx index of the byte to be verified
 * 
 * @return 0 in case of error, 1 otherwise
 */
int checkDiscEByteRecieved(unsigned char byte_recieved, int idx);

/**
 * @brief Verifies if the buf's bytes are equivalent to a UA sent by the transmitter
 * 
 * @param byte_recieved byte to be verified
 * @param idx index of the byte to be verified
 * 
 * @return 0 in case of error, 1 otherwise
 */
int checkUA_E_ByteRecieved(unsigned char byte_recieved, int idx);

/**
 * @brief Verifies if the data frame's header and tail are correct
 * 
 * @param frame frame to be verified
 * @param Nr sequence number
 * @param size frame size
 * 
 * @return 0 in case of error, 1 otherwise
 */
int checkDataFrame(unsigned char* frame, int Nr, int size);

/**
 * @brief Updates the llread state machine
 * 
 * @param c last byte read
 * @param state current state
 */
void handleIFrameState(char c, int* state);

/**
 * @brief Opens connection on the receiver side
 * 
 * @param port the name of the port file
 * @param fid the file descriptor to be passed to higher level functions (llopen)
 * @return negative value in case of error, positive otherwise
 */
int llopen_receiver(char* port, int* fid);

/**
 * @brief Closes connection on the receiver side
 * 
 * @param fd file descriptor of connection port file
 * @return negative value in case of error, positive otherwise
 */
int llclose_receiver(int fd);

#endif