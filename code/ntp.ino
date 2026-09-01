#include <WiFi.h>
#include <WiFiUdp.h>

unsigned long getNtpTime() {
    WiFiUDP udp;
    const char* ntpServer = "pool.ntp.org";
    const int ntpPort = 123;
    const int ntpPacketSize = 48;
    byte ntpPacket[ntpPacketSize];
    
    // Initialize the UDP connection
    udp.begin(ntpPort);
    
    // Prepare the NTP request packet
    memset(ntpPacket, 0, ntpPacketSize);
    ntpPacket[0] = 0b11100011; // LI, Version, Mode
    ntpPacket[1] = 0;          // Stratum
    ntpPacket[2] = 6;          // Polling Interval
    ntpPacket[3] = 0xEC;       // Precision
    
    // Send the NTP request packet to the server
    udp.beginPacket(ntpServer, ntpPort);
    udp.write(ntpPacket, ntpPacketSize);
    udp.endPacket();
    
    // Wait for a response (with a timeout)
    unsigned long startTime = millis();
    while (millis() - startTime < 1000) { // Wait for up to 1 second
        int packetSize = udp.parsePacket();
        if (packetSize >= ntpPacketSize) {
        udp.read(ntpPacket, ntpPacketSize);
    
        // Extract the timestamp from the response packet
        unsigned long highWord = word(ntpPacket[40], ntpPacket[41]);
        unsigned long lowWord = word(ntpPacket[42], ntpPacket[43]);
        unsigned long epochTime = (highWord << 16) | lowWord;
    
        // Convert NTP time to Unix time (subtracting the NTP epoch offset)
        const unsigned long seventyYears = 2208988800UL;
        return epochTime - seventyYears;
        }
        delay(10); // Small delay to avoid busy waiting
    }
    return 0; // Return 0 if no valid time is received
}