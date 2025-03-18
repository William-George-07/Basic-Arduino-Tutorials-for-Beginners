#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <LiquidCrystal.h>
QueueHandle_t queue_1;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);    //  RST E  D4 D5  D6 D7
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
queue_1 = xQueueCreate(5, sizeof(int));
  if (queue_1 == NULL) {
    Serial.println("Queue can not be created");
  }
  xTaskCreate(TaskDisplay, "Display_task", 128, NULL, 1, NULL);
  xTaskCreate(TaskLDR, "LDR_task", 128, NULL, 1, NULL);
  vTaskStartScheduler();
}
void loop() {
}
void TaskDisplay(void * pvParameters) {
  int intensity = 0;
  while(1) {
    Serial.println("TaskDisplay");
    if (xQueueReceive(queue_1, &intensity, portMAX_DELAY) == pdPASS) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Intensity:");
      lcd.setCursor(11, 0);
      lcd.print(intensity);
    }
  }
}
void TaskLDR(void * pvParameters) {
  int current_intensity; 
  while(1) {
    Serial.println("TaskLDR");
    current_intensity = analogRead(A0);
    Serial.println(current_intensity);
    xQueueSend(queue_1, ¤t_intensity, portMAX_DELAY);
    vTaskDelay( 1000 / portTICK_PERIOD_MS );
  }
}