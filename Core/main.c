#include "air32f10x.h"
#include "soft_i2c.h"
#include "air32f10x_conf.h"
#include "tx_api.h"

#define DEMO_STACK_SIZE         1024

#define GPIO_GROUP_TEST GPIOB
#define GPIO_MODE_TEST GPIO_Mode_Out_PP
#define GPIO_SPEED_TEST GPIO_Speed_50MHz
#define GPIO_PIN1_TEST GPIO_Pin_2
#define GPIO_PIN2_TEST GPIO_Pin_10
#define GPIO_PIN3_TEST GPIO_Pin_11

/* Define the ThreadX object control blocks...  */

TX_THREAD thread_0;
int a = 1;
int b = 1;
void GPIO_Configuration(void);

void thread_0_entry(ULONG thread_input);

int main(void) {
    GPIO_Configuration();
    tx_kernel_enter();
    a=2;
    b=3;
    while (1) {
    }
}

void tx_application_define(void *first_unused_memory) {

    /* Create a byte memory pool from which to allocate the thread stacks.  */

    /* Put system definition stuff in here, e.g. thread creates and other assorted
       create information.  */

    /* Allocate the stack for thread 0.  */

    /* Create the main thread.  */
    tx_thread_create(&thread_0, "thread 0", thread_0_entry, 0,
                     first_unused_memory, DEMO_STACK_SIZE,
                     1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);
}

void thread_0_entry(ULONG thread_input) {

    UINT status;


    /* This thread simply sits in while-forever-sleep loop.  */
    while (1) {

        /* Increment the thread counter.  */
        GPIO_SetBits(GPIO_GROUP_TEST, GPIO_PIN1_TEST);
        /* Sleep for 10 ticks.  */
        tx_thread_sleep(1000);
        GPIO_ResetBits(GPIO_GROUP_TEST, GPIO_PIN1_TEST);
        tx_thread_sleep(1000);

    }
}

void GPIO_Configuration(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能GPIOB时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_PIN1_TEST | GPIO_PIN2_TEST | GPIO_PIN3_TEST;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_TEST; //速度50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_TEST;     //输出模式
    GPIO_Init(GPIO_GROUP_TEST, &GPIO_InitStructure); //初始化GPIOB.2,10,11
}