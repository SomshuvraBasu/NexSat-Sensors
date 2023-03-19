#include "esp_camera.h"
#include "esp_timer.h"
#include "img_converters.h"
#include "Arduino.h"
#include "SD_MMC.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

// Pin definitions
#define SD_CS 13

// Camera configuration
const int CAMERA_XCLK = 0;
const int CAMERA_PCLK = 21;
const int CAMERA_VSYNC = 25;
const int CAMERA_HREF = 23;
const int CAMERA_SDA = 27;
const int CAMERA_SCL = 22;
const int CAMERA_D0 = 5;
const int CAMERA_D1 = 18;
const int CAMERA_D2 = 19;
const int CAMERA_D3 = 36;
const int CAMERA_D4 = 39;
const int CAMERA_D5 = 34;
const int CAMERA_D6 = 35;
const int CAMERA_D7 = 32;
const int CAMERA_TX = 4;
const int CAMERA_RX = 2;

// Buffer size for video recording
const int BUFFER_SIZE = 16000;

// File name for the video
const char *FILENAME = "/video.avi";

// Video size and frame rate
const framesize_t VIDEO_SIZE = FRAMESIZE_SVGA;
const int VIDEO_FPS = 30;

// Initialize the camera
void initCamera() {
  // Disable brownout detector
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
 
  // Initialize camera configuration
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = CAMERA_D0;
  config.pin_d1 = CAMERA_D1;
  config.pin_d2 = CAMERA_D2;
  config.pin_d3 = CAMERA_D3;
  config.pin_d4 = CAMERA_D4;
  config.pin_d5 = CAMERA_D5;
  config.pin_d6 = CAMERA_D6;
  config.pin_d7 = CAMERA_D7;
  config.pin_xclk = CAMERA_XCLK;
  config.pin_pclk = CAMERA_PCLK;
  config.pin_vsync = CAMERA_VSYNC;
  config.pin_href = CAMERA_HREF;
  config.pin_sscb_sda = CAMERA_SDA;
  config.pin_sscb_scl = CAMERA_SCL;
  config.pin_pwdn = -1;
  config.pin_reset = -1;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = VIDEO_SIZE;
  config.jpeg_quality = 10;
  config.fb_count = 1;
 
  // Initialize the camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera initialization error = %d\n", err);
    return;
  }
 
  // Set the frame rate
  sensor_t *sensor = esp_camera_sensor_get();
  sensor->set_framesize(sensor, VIDEO_SIZE);
  sensor->set_vflip(sensor, 1);
  sensor->set_hmirror(sensor, 1);
  sensor->set_framerate(sensor, VIDEO_FPS);
 
  Serial.println("Camera initialized");
}

void setup() {
  Serial.begin(115200);
 
  // Initialize the camera
  initCamera();
 
  // Initialize the SD card
  if (!SD_MMC.begin("/sdcard", true)) {
    Serial.println("SD card initialization failed!");
    return;
  }
 
  Serial.println("SD card initialized");
}

void loop() {
  // Open a new file for writing video
File videoFile = SD_MMC.open(FILENAME, FILE_WRITE);
if (!videoFile) {
Serial.println("Error opening video file for writing");
return;
}

Serial.println("Recording started");

uint8_t *buffer = (uint8_t *)malloc(BUFFER_SIZE);
if (!buffer) {
Serial.println("Error allocating buffer");
return;
}

uint32_t startTime = esp_timer_get_time();

while (true) {
size_t bytesRead = esp_camera_fb_get(buffer, BUFFER_SIZE);
if (bytesRead > 0) {
videoFile.write(buffer, bytesRead);
}
if (esp_timer_get_time() - startTime >= 1000000 / VIDEO_FPS) {
  break;
}
}
Serial.println("Recording finished")
videoFile.close();
free(buffer);
}

