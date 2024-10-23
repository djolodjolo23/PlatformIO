#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static int some_num = 0;

void my_func(void){
  int i = 0;
    for(i = 0; i < 1000000; i++){
        some_num++;
    }
}

extern "C" void app_main()
{
 while(true) {
    my_func();
    printf("some_num: %d\n", some_num);
 }

}