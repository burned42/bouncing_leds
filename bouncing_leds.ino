#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 2
#define PIXEL_COUNT 288
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_COUNT, PIN, NEO_GRB + NEO_KHZ800);

#define TD 0.075
#define BALL_COUNT 5
#define MAX_H (PIXEL_COUNT - 1)

#define G 9.8
#define A -G * TD
#define MAX_V sqrt(MAX_H * 2 * G)

struct Ball {
  float v;
  float h;
  int red;
  int green;
  int blue;
};

Ball balls[BALL_COUNT];

void setup() {
  pixels.begin();

  randomSeed(analogRead(1));

  for (int i = 0; i < BALL_COUNT; i++) {
    Ball ball;

    ball.v = MAX_V * (random(51) + 50) / 100;
    ball.h = 0;
    ball.red = random(256);
    ball.green = random(256);
    ball.blue = random(256);

    balls[i] = ball;
  }
}

void loop() {
  Serial.println("test");
  for (int i = 0; i < BALL_COUNT; i++) {
    float v = balls[i].v;
    float h = balls[i].h;


    h = min(
      double(MAX_H),
      max(
        0.0,
        (h + (v * TD) + (0.5 * A * TD * TD))
      )
    );

    if (h == 0) {
      v *= -0.75;
    }

    v += A;

    if ((int) v == 0 && (int) h == 0) {
      v = MAX_V * (random(6) + 95) / 100;
      balls[i].red = random(256);
      balls[i].green = random(256);
      balls[i].blue = random(256);
    }

    balls[i].v = v;
    balls[i].h = h;
  }

  pixels.clear();

  for (int b = 0; b < BALL_COUNT; b++) {
    pixels.setPixelColor((int) balls[b].h, balls[b].red, balls[b].green, balls[b].blue);
  }

  pixels.show();

  delay(5);
}

