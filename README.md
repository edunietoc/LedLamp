# LedLamp
RGB LED lamp based on ESP8266 board using web server on AP Mode

Connect: 
Red to D0
Green to D1
Blue to D2

upload sketch and enter "192.168.4.1" on browser, you'll see a simple UI with 3 sliders, each one of them controls a PWM output attached to the RGB LED.

At the beggining of the sketch we use #define 'pin_number' to use D0,D1,D2 pins of Wemos board. For another pin configuration, just change 'pin_number' with the gpio number of the pin associated Ex: 16 is pin D0.

