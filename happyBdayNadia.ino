#include <Arduino_MKRIoTCarrier.h>

MKRIoTCarrier carrier;

// Define the frequencies for each note in the "Happy Birthday" song
int notes[] = {
  262, 262, 294, 262, 349, 330,  // "Happy birthday to you"
  262, 262, 294, 262, 392, 349,  // "Happy birthday to you"
  262, 262, 523, 440, 349, 330, 294,  // "Happy birthday dear xx"
  466, 466, 440, 349, 392, 349   // "Happy birthday to you"
};

// Define the durations (in milliseconds) for each note
int durations[] = {
  500, 250, 750, 750, 750, 1000,  // "Happy birthday to you"
  500, 250, 750, 750, 750, 1000,  // "Happy birthday to you"
  500, 250, 750, 750, 750, 750, 1000,  // "Happy birthday dear xx"
  500, 250, 750, 750, 750, 1000   // "Happy birthday to you"
};

void setup() {
  // Initialize serial communication for debugging purposes
  Serial.begin(9600);
  
  // Wait for the serial monitor to open
  while (!Serial);

  // Initialize the MKR IoT Carrier
  CARRIER_CASE = true;
  if (!carrier.begin()) {
    Serial.println("Failed to initialize MKR IoT Carrier!");
    while (1);
  }
  delay(2000); // Pause for 2 seconds to initialize everything

  // Clear the display initially
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setTextColor(ST77XX_MAGENTA);
}

void loop() {
  // Display "3"
  carrier.display.setTextSize(6); // Adjust the text size for the countdown numbers
  displayMessage("3");
  delay(1000); // Wait for 1 second
  
  // Display "2"
  displayMessage("2");
  delay(1000); // Wait for 1 second
  
  // Display "1"
  displayMessage("1");
  delay(1000); // Wait for 1 second
  
  // Display "Buon Compleanno" on one line
  carrier.display.setTextSize(2); // Adjust text size for the message
  displayMessage("Buon Compleanno");
  delay(2000); // Wait for 2 seconds
  
  // Clear the screen before displaying "NADIA!"
  carrier.display.fillScreen(ST77XX_BLACK);
  
  // Display "NADIA!" on the next line
  carrier.display.setCursor(0, carrier.display.height() / 2); // Set cursor to the middle of the screen
  displayMessage("NADIA!");
  
  // Wait for 2 seconds before blinking all LEDs
  delay(2000);

  // Blink all LEDs 5 times
  for (int i = 0; i < 5; i++) {
    flashAllLeds();
    delay(500); // Delay between each blink
  }

    // Play the "Happy Birthday" song
  for (int i = 0; i < sizeof(notes) / sizeof(notes[0]); i++) {
    carrier.Buzzer.beep(notes[i], durations[i]);
  }
  
  // Add a long delay to keep the lights displayed
  delay(5000); // Wait for 5 seconds before repeating the loop
}

void displayMessage(const char* message) {
  // Clear the screen
  carrier.display.fillScreen(ST77XX_BLACK);
  
  // Get the width and height of the message to center it
  int16_t x1, y1;
  uint16_t w, h;
  carrier.display.getTextBounds(message, 0, 0, &x1, &y1, &w, &h);

  // Calculate the positions to center the text
  int16_t x = (carrier.display.width() - w) / 2;
  int16_t y = (carrier.display.height() - h) / 2;

  // Set the cursor to the calculated positions
  carrier.display.setCursor(x, y);

  // Display the message
  carrier.display.print(message);
  
  Serial.println(message); // For debugging purposes, output to Serial Monitor
}

void flashAllLeds() {
  // Set all RGB LEDs to green color
  for (int i = 0; i < carrier.leds.numPixels(); i++) {
    carrier.leds.setPixelColor(i, carrier.leds.Color(0, 255, 0));
  }
  
  carrier.leds.show(); // Update LEDs
  
  delay(100); // Delay before turning off
  
  // Turn off all RGB LEDs
  carrier.leds.clear(); // Clear all RGB LEDs
  carrier.leds.show(); // Update LEDs
  
  delay(100); // Delay before next blink
}