#ifndef MySSD1306_Enchanced_h
#define MySSD1306_Enchanced_h

#include <Adafruit_SSD1306.h>

#include <sstream>
#include <string>

// Дефолтный отступ
#ifndef SSD1306_LINE_SPACING
  #define SSD1306_LINE_SPACING 10
#endif

#ifndef SCREEN_WIDTH
  #define SCREEN_WIDTH 128
#endif

#ifndef SCREEN_HEIGHT
  #define SCREEN_HEIGHT 64
#endif

class MySSD1306 : public Adafruit_SSD1306 {
public:
    MySSD1306(uint8_t w, uint8_t h, TwoWire *twi = &Wire, int8_t rst_pin = -1);
    
    // Управление отступом
    void setLineSpacing(int16_t spacing);
    int16_t getLineSpacing();
    
    // ========== СТАНДАРТНЫЕ PRINTLN (все типы) ==========
    void println(const char str[]);
    void println(const String &s);
    void println(char c);
    void println(unsigned char c);
    void println(int n);
    void println(unsigned int n);
    void println(long n);
    void println(unsigned long n);
    void println(double n, int digits = 2);
    void println(void);
    
    // ========== PRINTLN CENTER (все типы) ==========
    void printlnCenter(const char str[]);
    void printlnCenter(const String &s);
    void printlnCenter(char c);
    void printlnCenter(unsigned char c);
    void printlnCenter(int n);
    void printlnCenter(unsigned int n);
    void printlnCenter(long n);
    void printlnCenter(unsigned long n);
    void printlnCenter(double n, int digits = 2);
    
    // ========== PRINTLN WRAPPED (все типы) ==========
    void printlnWrapped(const char str[]);
    void printlnWrapped(const String &s);
    void printlnWrapped(char c);
    void printlnWrapped(unsigned char c);
    void printlnWrapped(int n);
    void printlnWrapped(unsigned int n);
    void printlnWrapped(long n);
    void printlnWrapped(unsigned long n);
    void printlnWrapped(double n, int digits = 2);
    
    // Дополнительные полезные методы
    void setCharWidth(int width);
    int getCharWidth();
    void setVerticalOffset(int offset);
    
private:
    int16_t _lineSpacing = SSD1306_LINE_SPACING;
    int _charWidth = 6;          // Ширина символа в пикселях (для std шрифта)
    int _verticalOffset = -8;    // Вертикальное смещение при центрировании
    
    void moveCursorAfterPrint();
    String toString(char c);
    String toString(unsigned char c);
    String toString(int n);
    String toString(unsigned int n);
    String toString(long n);
    String toString(unsigned long n);
    String toString(double n, int digits = 2);
    
    int getTextWidth(const String &text);
    void printlnCenterInternal(const String &text);
    void printlnWrappedInternal(const String &text);
};

#endif