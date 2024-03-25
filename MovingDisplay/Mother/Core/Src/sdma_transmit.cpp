
#include "sdma_transmit.h"

SDMA_TRANSMIT::SDMA_TRANSMIT(UART_HandleTypeDef* uart, uint8_t id){
    UART = uart;
    ID = id;
}

void SDMA_TRANSMIT::begin_dma(){
    HAL_UART_Receive_DMA(UART, rxBuf, sizeof(rxBuf));
    HAL_Delay(1);
}

void SDMA_TRANSMIT::check_buf(){
	index = UART->hdmarx->Instance->NDTR;//バッファー残容量
 	index = sizeof(rxBuf) - index;//最新の受信データ位置

 	int check_buf_point = index - 10;
 	if(check_buf_point < 0){check_buf_point = check_buf_point + sizeof(rxBuf);}
 	//読み込み済みデータ位置より最新の受信データ位置が前にある時(バッファー内で受信データが一周してた場合)値を補正

	while(1){
		readData = rxBuf[check_buf_point];
		if(readData == 250+ID){
			for(int i=1; i<5; i++){
				int read_buf_point = check_buf_point + i;
				if(read_buf_point>sizeof(rxBuf)-1){read_buf_point = read_buf_point - sizeof(rxBuf);}
				rcvBuf[i-1] = rxBuf[read_buf_point];
			}
			break;
		}
		check_buf_point++;
		if(check_buf_point>sizeof(rxBuf)-1){check_buf_point = check_buf_point - sizeof(rxBuf);}
		if(check_buf_point==index){break;}
	}

 	mode = rcvBuf[0];

	clock = 0;
 	int hyaku = 1;
	for(int i = 1; i <3 ; i++){
		clock = clock + (rcvBuf[i]*hyaku);
		hyaku = hyaku*240;
	}

	hue = rcvBuf[4];

}

/*
void SDMA_TRANSMIT::send_data(long data){
    send_array[0]=190+ID;
    data += 5000;

    if(data<0){data=9999;}
    else if(data>9999){data=9999;}

	for(int i = 1; i <3 ;i++){
		send_array[i] = data%100;
		data = (int)data/100;
	}
    HAL_UART_Transmit(UART, send_array, 3, 100);
}
*/

