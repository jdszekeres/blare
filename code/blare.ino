#include <Adafruit_GFX.h> // graphics library
#include <Adafruit_ST7789.h> // driver for the ST7789 screen
#include <SPI.h> 
#include <WiFi.h>

#include <ntp.ino> // Include the NTP time function from ntp.ino

// Defining pins for the display, change according to your setup!!! Uses the white numbers on the ESP
#define TFT_SCLK 0 // labeled SCL on the screen
#define TFT_MOSI 1 // labeled SDA on the screen
#define TFT_RST 2
#define TFT_DC 3
#define TFT_CS 4
#define TFT_BL 5

// Fix setColRowStart() by exposing it via a subclass
class MyST7789 : public Adafruit_ST7789 {
public:
  MyST7789(int8_t cs, int8_t dc, int8_t mosi, int8_t sclk, int8_t rst)
    : Adafruit_ST7789(cs, dc, mosi, sclk, rst) {}
  void setOffsets(uint8_t col, uint8_t row) {
    _colstart = _colstart2 = col;
    _rowstart = _rowstart2 = row;
  }
};

MyST7789 tft(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


unsigned long epochTime = 0; // Variable to store the epoch time

unsigned long currentMillis = 0; // Variable to store the current time in milliseconds

unsigned long lastUpdatedMillis = 0; // Variable to store the last update time in milliseconds
unsigned long lastUpdateTime = 0; // Variable to store the last update time


void setup() {
  Serial.begin(115200); // lets the board talk to your computer

  pinMode(TFT_BL, OUTPUT); // Set the backlight pin mode, or just wire it to 3.3V
  digitalWrite(TFT_BL, LOW); // Turns the backlight ON, for some reason this screen is active Low, so setting it to LOW is really HIGH

  tft.init(76, 284); // Our panel size (portrait)
  tft.setOffsets(82, 18); // Offsets for the weird resolution
  tft.invertDisplay(false); // Invert the colors (This display is flipped from normal)
  tft.setRotation(1); // Landscape, if it's upside down use 3!
  Serial.println("TFT Initialized!");

  tft.fillScreen(ST77XX_BLACK); // clear the screen

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(6);
  tft.setCursor(0,0); // Where the text is drawn, 0,0 is top left
  tft.print("Hello, World!"); // Show whatever you want! Draws from the top left of the text/number/shape 


  WiFi.begin("SSID", "PASSWORD"); // Connect to WiFi, change to your network
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  epochTime = getNtpTime(); // Get the current epoch time from the NTP server
  lastUpdateTime = epochTime; // Initialize the last update time
  lastUpdatedMillis = millis(); // Initialize the last update time in milliseconds
  currentMillis = millis(); // Initialize the current time in milliseconds


}


// loop() runs OVER and OVER, forever
void loop() {

    if (epochTime - lastUpdateTime > 1800) { //update time every half hour
        // If more than 1 second has passed, fetch the current time from the NTP server
        epochTime = getNtpTime();
        lastUpdateTime = epochTime; // Update the last update time
        lastUpdatedMillis = millis(); // Update the last update time in milliseconds
        currentMillis = millis(); // Reset the current time in milliseconds
    }

    // Calculate the current epoch time based on the last update and elapsed time
    currentMillis = millis(); // Update the current time in milliseconds
    unsigned long elapsedMillis = currentMillis - lastUpdatedMillis; // Calculate elapsed time since last

    unsigned long currentEpoch = lastUpdateTime + (elapsedMillis / 1000); // Calculate the current epoch time

    // Convert epoch time to human-readable format
    int hours = (currentEpoch % 86400L) / 3600; // Calculate hours
    int minutes = (currentEpoch % 3600) / 60;   // Calculate minutes
    int seconds = currentEpoch % 60;            // Calculate seconds

    // Display the time on the TFT screen
    tft.fillScreen(ST77XX_BLACK); // Clear the screen
    tft.setCursor(0, 0);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(6);
    tft.printf("%02d:%02d:%02d", hours, minutes, seconds); // Print time in HH:MM:SS format

}