#include <uart.h>

#define LOG_MESSAGE_TEMPLATE(TYPE,MESSAGE)  uart_write_string(TYPE); \
					  						uart_write_ascii('('); \
					  						uart_write_string(__FILE__); \
					  						uart_write_ascii(' '); \
					  						uart_write_string(__FUNCTION__); \
					  						uart_write_ascii(':'); \
					  						uart_write_number(__LINE__); \
					  						uart_write_string(")\n  "); \
					  						uart_write_string(MESSAGE)

#define log_info(message) {uart_write_string("\033[0;32m"); \
						  LOG_MESSAGE_TEMPLATE("[Info]",message); \
						  uart_write_string("\033[0m \n\n");}

#define log_critical(message) {uart_write_string("\033[0;31m"); \
						   	 LOG_MESSAGE_TEMPLATE("[Critical]",message); \
						   	 uart_write_string("\033[0m \n\n");}

#define log_debug(message) {uart_write_string("\033[0;36m"); \
						   	 LOG_MESSAGE_TEMPLATE("[Debug]",message); \
						   	 uart_write_string("\033[0m \n\n");}

#define log_info_number(message,number) {uart_write_string("\033[0;32m"); \ 
							     LOG_MESSAGE_TEMPLATE("[Info]",message); \
							     uart_write_number(number); \
							     uart_write_string("\033[0m \n\n");}
							     
#define log_crtical_number(message,number) {uart_write_string("\033[0;31m"); \ 
							     LOG_MESSAGE_TEMPLATE("[Critical]",message); \
							     uart_write_number(number); \
							     uart_write_string("\033[0m \n\n");}

#define log_debug_number(message,number) {uart_write_string("\033[0;36m"); \ 
							     LOG_MESSAGE_TEMPLATE("[Debug]",message); \
							     uart_write_number(number); \
							     uart_write_string("\033[0m \n\n");}
