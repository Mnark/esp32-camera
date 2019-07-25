#include "esp_log.h"
#include "esp_camera.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_spiram.h"

static const char *TAG = "main";

#define PWDN_GPIO_NUM 32  //32
#define RESET_GPIO_NUM -1 // Not exposed
#define XCLK_GPIO_NUM 0   //0  //CONFIG_XCLK=0 Leave this floating
#define SIOD_GPIO_NUM 26  //CONFIG_SDA = 26
#define SIOC_GPIO_NUM 27  //CONFIG_SCL=27
#define Y9_GPIO_NUM 35    //CONFIG_D7 = 35
#define Y8_GPIO_NUM 34    //CONFIG_D6 = 34
#define Y7_GPIO_NUM 39    //CONFIG_D5 = 39
#define Y6_GPIO_NUM 36    //CONFIG_D4 = 36
#define Y5_GPIO_NUM 21    //CONFIG_D3 = 21
#define Y4_GPIO_NUM 19    //CONFIG_D2 = 19
#define Y3_GPIO_NUM 18    //CONFIG_D1 = 18
#define Y2_GPIO_NUM 5     //CONFIG_D0 = 5
#define VSYNC_GPIO_NUM 25 //CONFIG_VSYNC=25
#define HREF_GPIO_NUM 23  //CONFIG_HREF=23
#define PCLK_GPIO_NUM 22  //CONFIG_PCLK=22

static camera_config_t camera_config = {
    .ledc_channel = LEDC_CHANNEL_0,
    .ledc_timer = LEDC_TIMER_0,
    .pin_d0 = Y2_GPIO_NUM,
    .pin_d1 = Y3_GPIO_NUM,
    .pin_d2 = Y4_GPIO_NUM,
    .pin_d3 = Y5_GPIO_NUM,
    .pin_d4 = Y6_GPIO_NUM,
    .pin_d5 = Y7_GPIO_NUM,
    .pin_d6 = Y8_GPIO_NUM,
    .pin_d7 = Y9_GPIO_NUM,
    .pin_xclk = XCLK_GPIO_NUM,
    .pin_pclk = PCLK_GPIO_NUM,
    .pin_vsync = VSYNC_GPIO_NUM,
    .pin_href = HREF_GPIO_NUM,
    .pin_sscb_sda = SIOD_GPIO_NUM,
    .pin_sscb_scl = SIOC_GPIO_NUM,
    .pin_pwdn = PWDN_GPIO_NUM,
    .pin_reset = RESET_GPIO_NUM,
    //.xclk_freq_hz = 10000000,
    .xclk_freq_hz = 20000000,
    .pixel_format = PIXFORMAT_JPEG,
    //init with high specs to pre-allocate larger buffers
    .frame_size = FRAMESIZE_UXGA,
    .jpeg_quality = 10,
    .fb_count = 2};

void app_main()
{

    // //Internal RAM
    // printf("Internal Total heap %d, internal Free Heap %d\n", ESP.getHeapSize(), ESP.getFreeHeap());
    // //SPI RAM
    // printf("SPIRam Total heap %d, SPIRam Free Heap %d\n", ESP.getPsramSize(), ESP.getFreePsram());

    // printf("ChipRevision %d, Cpu Freq %d, SDK Version %s\n", ESP.getChipRevision(), ESP.getCpuFreqMHz(), ESP.getSdkVersion());

    // printf(" Flash Size %d, Flash Speed %d\n", ESP.getFlashChipSize(), ESP.getFlashChipSpeed());

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("sccb", ESP_LOG_DEBUG);
    esp_log_level_set("camera", ESP_LOG_DEBUG);
    esp_log_level_set("xclk", ESP_LOG_DEBUG);
    esp_log_level_set("gpio", ESP_LOG_INFO);
    esp_err_t err;

    ESP_LOGI(TAG, "Starting main program");

    err = esp_camera_init(&camera_config);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "* Failed to initialise camera. Error: %d", err);
        goto fail;
    }

    ESP_LOGI(TAG, "Testing Camera");
    camera_fb_t *fb = esp_camera_fb_get();
    if (fb != NULL)
    {
        ESP_LOGI(TAG, ">>> Success ");
    }
    else
    {
        ESP_LOGE(TAG, ">>> NULL frame returned from camera ");
    }
    esp_camera_fb_return(fb);

fail:
    ESP_LOGI(TAG, "Program Ended");
}