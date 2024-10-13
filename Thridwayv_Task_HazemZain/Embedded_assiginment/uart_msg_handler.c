#include "uart.h"
// TODO: implement the "uart_msg_handler.h" file.
#include "uart_msg_handler.h"

 
/*
*	@function	uart_recevied_msg_cb(char received_char).
*	@brief		This is a callback function called in the uart module ISR.
*				Each time the uart module recieves a byte, It calls this function.
*				The purpose of this is function is to make sure that the messege recieved is a valid message.
*				For a message to be valid it needs to follow the following patters.
*				[magic_pattern_byte1] [magic_pattern_byte2] [message_length_byte1] [message_length_byte2] [message].
*				magic_pattern: ['T','W']. A 2 byte pattern that marks the beginning of the message.
*				message_length: is the length of the received message. The UART message length can be up to 16 bit number.
 *              It is received in the the two bytes message_length_byte1 and message_length_byte2.
*	@param  	received_char: The received byte from the the UART Hal.

*/

#define magic_pattern_byte1 'T'
#define magic_pattern_byte2 'W'
int check_Start_Frame_Flag=0;
char Message_buffer[255]; //The UART message length can be up to 16 bit number.
int Message_Index=0;
uint16_t Message_lenght=0;
tpf_uart_msg_handler_recv_cb app_callback = NULL;


static void uart_recevied_msg_cb(char received_char){
	// TODO: check if valid massege.
	
	//no message received until now
	if(check_Start_Frame_Flag==0){
		if(Message_Index==0 && received_char==magic_pattern_byte1 ){
			Message_buffer[Message_Index++]=received_char;
		}else if(Message_Index==1 && received_char==magic_pattern_byte2)
		{
			Message_buffer[Message_Index++]=received_char;
			check_Start_Frame_Flag=1; //start recuve message lenght and message
		}else{
			Message_Index=0; //reset the message buffer 
		}
		
	}else if(check_Start_Frame_Flag==1){
		Message_buffer[Message_Index++]=received_char;
		if(Message_Index==4)//this main that the lenght for message is in buffer [byte 2 and byte 3]
		{
			uint16_t len1=(uint8_t)Message_buffer[2];
			uint16_t len2=(uint8_t)Message_buffer[3];
			Message_lenght=len1<<8|len2;
			
			if(Message_lenght>255-4) // if we recive invalid lenght we will reset all thing
			{
				Message_Index=0; //reset the message buffer 
				check_Start_Frame_Flag=0;
				return;				
			}
			
		}else if(Message_Index==Message_lenght+4) //the full  message is recived 
		{
			//Call Print Message form App
			// TODO: call the callback function of the app layer.
			app_callback(&Message_buffer[4],Message_lenght);
		}
	}
	
}


void uart_handler_init(char uart_channel_num, tpf_uart_msg_handler_recv_cb pf_uart_msg_handler_recv_cb){
	uart_init(uart_channel_num, uart_recevied_msg_cb);
	// TODO: Implement the 'tpf_uart_msg_handler_recv_cb' type.
	//typedef void (*tpf_uart_msg_handler_recv_cb)(char *msg_buf, int msg_length); in header file
	// TODO: Assign the 'pf_uart_msg_handler_recv_cb' parameter to the callback function to be called after finished receiving.
	app_callback=pf_uart_msg_handler_recv_cb;
}


void uart_send_msg(char *msg_buf, int msg_length){
	uart_send(msg_buf, msg_length);
}
