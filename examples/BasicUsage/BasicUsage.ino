#include <Wire.h>
#include <Adafruit_SSD1306_Enhanced.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

MySSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
    Serial.begin(115200);
    
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println("SSD1306 allocation failed");
        for(;;);
    }
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    
    // Демонстрация возможностей
    display.println("Standard println");
    display.println(123);
    
    display.printlnCenter("Centered text");
    display.printlnCenter(3.14159);
    
    display.printlnWrapped("This is a very long text that will wrap automatically");
    
    display.display();
}

void loop() {}
