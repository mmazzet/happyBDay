#include <Arduino_MKRIoTCarrier.h>

MKRIoTCarrier carrier;

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
  
  // Display "Happy" on one line and "Birthday!" on the next line
  carrier.display.setTextSize(2); // Adjust text size for the message
  displayMessage("Buon Compleanno");
  delay(2000);
  carrier.display.setCursor(0, carrier.display.height() / 2); // Set cursor to the middle of the screen
  displayMessage("NADIA!");
  
  // Add a long delay to keep the message displayed
  delay(5000); // Wait for 5 seconds before repeating the loop
}

void displayMessage(const char* message) {
  // Clear the screen
  carrier.display.fillScreen(ST77XX_GREEN);
  
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