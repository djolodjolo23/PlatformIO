#include "display.h"
#include "spaghetti_oled_image.h"

display::display(U8G2 &u8g2_instance) : u8g2(u8g2_instance) {
}

void display::clearArrowArea() {
    u8g2.setDrawColor(0);  
    u8g2.drawBox(30, 30, 68, 68); 
    u8g2.setDrawColor(1);
}

void display::spaghetti() {
    clearArrowArea();
    u8g2.drawXBM(5, 5, 96, 96, oled_image);
    u8g2.sendBuffer();
}

void display::hamburger() {
    clearArrowArea();

    // Top bun (arc)
    u8g2.drawEllipse(64, 50, 32, 10, U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_UPPER_LEFT); 
    
    // Patty (rectangle)
    u8g2.drawBox(32, 60, 64, 8);  // (x, y, width, height)

    // Cheese (triangle)
    u8g2.drawTriangle(48, 60, 80, 60, 64, 68);  // Draw cheese as a triangle below patty

    // Bottom bun (arc)
    u8g2.drawEllipse(64, 72, 32, 8, U8G2_DRAW_LOWER_RIGHT | U8G2_DRAW_LOWER_LEFT); 

    u8g2.sendBuffer();
}

void display::randomWavyLineInCircle() {
    clearArrowArea();

    // Circle center and radius
    int centerX = 64;
    int centerY = 64;
    int radius = 30;

    // 1. Draw the circle
    u8g2.drawCircle(centerX, centerY, radius, U8G2_DRAW_ALL);  // Draw the boundary of the circle

    // 2. Random starting point on the edge of the circle
    float startAngle = random(0, 360) * 3.14159 / 180;  // Convert to radians
    int x = centerX + radius * cos(startAngle);  // Starting x coordinate on the circle
    int y = centerY + radius * sin(startAngle);  // Starting y coordinate on the circle
    
    // Draw the first point (starting point of the wavy line)
    u8g2.drawPixel(x, y);

    // 3. Create a wavy line with a total length of 20
    int length = 0;
    while (length < 20) {
        // Random small angle deviation (in radians)
        float angleChange = random(-30, 30) * 3.14159 / 180;  // Random deviation between -30 and 30 degrees
        
        // Move a small step in the new random direction
        int stepSize = 2;  // Step size for each segment of the wavy line
        int newX = x + stepSize * cos(startAngle + angleChange);  // New x coordinate
        int newY = y + stepSize * sin(startAngle + angleChange);  // New y coordinate
        
        // Check if the new point is inside the circle
        if ((newX - centerX) * (newX - centerX) + (newY - centerY) * (newY - centerY) <= radius * radius) {
            // If inside the circle, draw the line segment from (x, y) to (newX, newY)
            u8g2.drawLine(x, y, newX, newY);
            
            // Update current position to the new point
            x = newX;
            y = newY;
            
            // Increase the total length of the wavy line
            length += stepSize;
        }
    }

    u8g2.sendBuffer();
}




void display::biryani() {
    clearArrowArea();

    // Plate (circle)
    u8g2.drawCircle(64, 64, 30, U8G2_DRAW_ALL);  // Centered at (64, 64) with radius 30

    // Rice (random dots)
    for (int i = 40; i < 90; i += 5) {
        for (int j = 40; j < 90; j += 5) {
            u8g2.drawPixel(i + (rand() % 3 - 1), j + (rand() % 3 - 1));  // Random dots for rice
        }
    }

    // Chicken/vegetable pieces (rectangles or triangles)
    u8g2.drawBox(54, 54, 8, 8);  // First piece
    u8g2.drawBox(70, 68, 10, 6); // Second piece
    
    u8g2.sendBuffer();
}



void display::rightArrow() {
    clearArrowArea();
    u8g2.drawLine(32, 64, 96, 64);  
    u8g2.drawLine(96, 64, 86, 54); 
    u8g2.drawLine(96, 64, 86, 74);  
    u8g2.sendBuffer();
}

void display::leftArrow() {
    clearArrowArea();
    u8g2.drawLine(96, 64, 32, 64);  
    u8g2.drawLine(32, 64, 42, 54);  
    u8g2.drawLine(32, 64, 42, 74);  
    u8g2.sendBuffer();
}

void display::upArrow() {
    clearArrowArea();
    u8g2.drawLine(64, 32, 64, 96);  
    u8g2.drawLine(64, 32, 54, 42);  
    u8g2.drawLine(64, 32, 74, 42);  
    u8g2.sendBuffer();
}

void display::downArrow() {
    clearArrowArea();
    u8g2.drawLine(64, 96, 64, 32);  
    u8g2.drawLine(64, 96, 54, 86);  
    u8g2.drawLine(64, 96, 74, 86); 
    u8g2.sendBuffer();
}

void display::showCoordinates(String text1, String text2) {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    
    u8g2.setDrawColor(0);
    u8g2.drawBox(0, 0, 128, 16);
    u8g2.setDrawColor(1);
    u8g2.drawStr(0, 10, text1.c_str());

    u8g2.setDrawColor(0);
    u8g2.drawBox(0, 112, 128, 16);
    u8g2.setDrawColor(1);
    u8g2.drawStr(0, 126, text2.c_str());

    u8g2.sendBuffer();
}