#ifndef UART_MSG_HANDLER_H
#define UART_MSG_HANDLER_H
typedef void (*tpf_uart_msg_handler_recv_cb)(char *msg_buf, int msg_length);
static void uart_recevied_msg_cb(char received_char);
void uart_handler_init(char uart_channel_num, tpf_uart_msg_handler_recv_cb pf_uart_msg_handler_recv_cb);
void uart_send_msg(char *msg_buf, int msg_length);
#endif
