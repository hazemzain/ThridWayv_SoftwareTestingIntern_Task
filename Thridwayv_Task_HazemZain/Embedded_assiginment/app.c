#include "uart_msg_handler.h"
#include "lcd.h"
#include "app.h"


/*
*	@function	print_msg_cb(char *msg_buf, int msg_length).
*	@brief		This is the callback function from the uart_msg_handler.
*	            It logs the received date.
*	@param  	*msg_buf: start adress of the message buffer.
*               msg_length: Length of the message buffer.
*/
static void print_msg_cb(char *msg_buf, int msg_length){
	
	log("data_length = %d.\n");
	log("data =/n");
	
	int print_counter = 0;
	
	while (print_counter <= msg_length) {
		
		printf("%02hhx ", msg_buf[print_counter]);
		print_counter ++;
		
		if(print_counter%16 == 0){
			log("\n");
		}
		
    }
	
}


/*
*	@function	app_init().
*	@brief		This function is called only one time in the beginning of the program.
*	            It used to initialize any module used in the program.
*/
static void app_init(){
	// TODO: call the uart_handler_init.
	 uart_handler_init(0,print_msg_cb );
}


static void main(){
	app_init();
	while(1);
}