#include "MySSD1306_Enchanced.h"

MySSD1306::MySSD1306(uint8_t w, uint8_t h, TwoWire *twi, int8_t rst_pin)
    : Adafruit_SSD1306(w, h, twi, rst_pin) 
{
}

void MySSD1306::setLineSpacing(int16_t spacing) {
    _lineSpacing = spacing;
}

int16_t MySSD1306::getLineSpacing() {
    return _lineSpacing;
}

void MySSD1306::setCharWidth(int width) {
    _charWidth = width;
}

int MySSD1306::getCharWidth() {
    return _charWidth;
}

void MySSD1306::setVerticalOffset(int offset) {
    _verticalOffset = offset;
}

void MySSD1306::moveCursorAfterPrint() {
    setCursor(getCursorX(), getCursorY() + _lineSpacing);
}

int MySSD1306::getTextWidth(const String &text) {
    // Можно использовать реальное измерение через getTextBounds
    int16_t x1, y1;
    uint16_t w, h;
    getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    if (w > 0) return w;
    return text.length() * _charWidth;  // fallback
}

// ========== КОНВЕРТАЦИЯ В STRING ==========
String MySSD1306::toString(char c) {
    return String(c);
}

String MySSD1306::toString(unsigned char c) {
    return String(c);
}

String MySSD1306::toString(int n) {
    return String(n);
}

String MySSD1306::toString(unsigned int n) {
    return String(n);
}

String MySSD1306::toString(long n) {
    return String(n);
}

String MySSD1306::toString(unsigned long n) {
    return String(n);
}

String MySSD1306::toString(double n, int digits) {
    return String(n, digits);
}

// ========== СТАНДАРТНЫЕ PRINTLN ==========
void MySSD1306::println(const char str[]) {
    Adafruit_SSD1306::print(str);
    moveCursorAfterPrint();
}

void MySSD1306::println(const String &s) {
    Adafruit_SSD1306::print(s);
    moveCursorAfterPrint();
}

void MySSD1306::println(char c) {
    Adafruit_SSD1306::print(c);
    moveCursorAfterPrint();
}

void MySSD1306::println(unsigned char c) {
    Adafruit_SSD1306::print(c);
    moveCursorAfterPrint();
}

void MySSD1306::println(int n) {
    Adafruit_SSD1306::print(n);
    moveCursorAfterPrint();
}

void MySSD1306::println(unsigned int n) {
    Adafruit_SSD1306::print(n);
    moveCursorAfterPrint();
}

void MySSD1306::println(long n) {
    Adafruit_SSD1306::print(n);
    moveCursorAfterPrint();
}

void MySSD1306::println(unsigned long n) {
    Adafruit_SSD1306::print(n);
    moveCursorAfterPrint();
}

void MySSD1306::println(double n, int digits) {
    Adafruit_SSD1306::print(n, digits);
    moveCursorAfterPrint();
}

void MySSD1306::println(void) {
    Adafruit_SSD1306::println();
    moveCursorAfterPrint();
}

// ========== PRINTLN CENTER (внутренний) ==========
void MySSD1306::printlnCenterInternal(const String &text) {
    int textWidth = getTextWidth(text);
    int centerX = (width() - textWidth) / 2;
    int centerY = (height() / 2) + _verticalOffset;
    
    // Запоминаем позицию для восстановления
    int oldX = getCursorX();
    int oldY = getCursorY();
    
    if (textWidth <= width()) {
        setCursor(centerX, centerY);
        println(text);
    } else {
        setCursor(0, centerY);
        printlnWrappedInternal(text);
    }
}

// ========== PRINTLN CENTER (все типы) ==========
void MySSD1306::printlnCenter(const char str[]) {
    printlnCenterInternal(String(str));
}

void MySSD1306::printlnCenter(const String &s) {
    printlnCenterInternal(s);
}

void MySSD1306::printlnCenter(char c) {
    printlnCenterInternal(toString(c));
}

void MySSD1306::printlnCenter(unsigned char c) {
    printlnCenterInternal(toString(c));
}

void MySSD1306::printlnCenter(int n) {
    printlnCenterInternal(toString(n));
}

void MySSD1306::printlnCenter(unsigned int n) {
    printlnCenterInternal(toString(n));
}

void MySSD1306::printlnCenter(long n) {
    printlnCenterInternal(toString(n));
}

void MySSD1306::printlnCenter(unsigned long n) {
    printlnCenterInternal(toString(n));
}

void MySSD1306::printlnCenter(double n, int digits) {
    printlnCenterInternal(toString(n, digits));
}

// ========== PRINTLN WRAPPED (внутренний) ==========
void MySSD1306::printlnWrappedInternal(const String &text) {
    int start = 0;
    int spaceIndex;
    int currentX;
    int lineWidth;
    
    int oldCursorY = getCursorY();
    setCursor(0, oldCursorY);
    
    while ((spaceIndex = text.indexOf(' ', start)) != -1) {
        String word = text.substring(start, spaceIndex);
        currentX = getCursorX();
        lineWidth = currentX + getTextWidth(word);
        
        if (lineWidth + getTextWidth(" ") <= width()) {
            print(word);
            print(" ");
        } else {
            if (currentX > 0) {
                println();
                setCursor(0, getCursorY());
            }
            print(word);
            print(" ");
        }
        start = spaceIndex + 1;
    }
    
    // Последнее слово/часть
    String lastWord = text.substring(start);
    currentX = getCursorX();
    lineWidth = currentX + getTextWidth(lastWord);
    
    if (lineWidth <= width()) {
        print(lastWord);
    } else {
        if (currentX > 0) {
            println();
            setCursor(0, getCursorY());
        }
        print(lastWord);
    }
    
    println();  // Финальный перевод строки
}

// ========== PRINTLN WRAPPED (все типы) ==========
void MySSD1306::printlnWrapped(const char str[]) {
    printlnWrappedInternal(String(str));
}

void MySSD1306::printlnWrapped(const String &s) {
    printlnWrappedInternal(s);
}

void MySSD1306::printlnWrapped(char c) {
    printlnWrappedInternal(toString(c));
}

void MySSD1306::printlnWrapped(unsigned char c) {
    printlnWrappedInternal(toString(c));
}

void MySSD1306::printlnWrapped(int n) {
    printlnWrappedInternal(toString(n));
}

void MySSD1306::printlnWrapped(unsigned int n) {
    printlnWrappedInternal(toString(n));
}

void MySSD1306::printlnWrapped(long n) {
    printlnWrappedInternal(toString(n));
}

void MySSD1306::printlnWrapped(unsigned long n) {
    printlnWrappedInternal(toString(n));
}

void MySSD1306::printlnWrapped(double n, int digits) {
    printlnWrappedInternal(toString(n, digits));
}