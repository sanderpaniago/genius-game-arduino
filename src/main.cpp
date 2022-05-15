#include <Arduino.h>

const int pino_ledG = 11;
const int pino_ledR = 10;
const int pino_ledY = 9;
const int pino_ledW = 8;

const int pino_buttonG = 7;
const int pino_buttonR = 6;
const int pino_buttonY = 5;
const int pino_buttonW = 4;

const int pino_buzzer = 3;

const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int soundError = 100;

int level = 0, i, compara = 0;
long notas[50], resultado[50];

bool flag = LOW, flag_bG = LOW, flag_bR = LOW, flag_bY = LOW, flag_bW = LOW, decrease = LOW;

void animation();
void validPlayUser(int pino_led, int tone_play);

void setup() {
  pinMode(pino_ledG, OUTPUT);
  pinMode(pino_ledR, OUTPUT);
  pinMode(pino_ledY, OUTPUT);
  pinMode(pino_ledW, OUTPUT);

  pinMode(pino_buttonG, INPUT_PULLUP);
  pinMode(pino_buttonR, INPUT_PULLUP);
  pinMode(pino_buttonY, INPUT_PULLUP);
  pinMode(pino_buttonW, INPUT_PULLUP);

  pinMode(pino_buzzer, OUTPUT);

  animation();
}

void loop() {

  notas[level] = random(1, 5);
  delay(10);

  for (i = 0; i < level; i++) {
    if (notas[i] == 1) {
      tone(pino_buzzer, c);
      digitalWrite(pino_ledG, HIGH);
      delay(500);
      noTone(pino_buzzer);
      digitalWrite(pino_ledG, LOW);
    } else if (notas[i] == 2) {
      tone(pino_buzzer, d);
      digitalWrite(pino_ledR, HIGH);
      delay(500);
      noTone(pino_buzzer);
      digitalWrite(pino_ledR, LOW);
    } else if (notas[i] == 3) {
      tone(pino_buzzer, e);
      digitalWrite(pino_ledY, HIGH);
      delay(500);
      noTone(pino_buzzer);
      digitalWrite(pino_ledY, LOW);
    } else if (notas[i] == 4) {
      tone(pino_buzzer, f);
      digitalWrite(pino_ledW, HIGH);
      delay(500);
      noTone(pino_buzzer);
      digitalWrite(pino_ledW, LOW);
    } 

    delay(500);
  }

  flag = HIGH;
  i = 0;
  compara = 0;

  while (flag == HIGH) {
  int value_buttonG = digitalRead(pino_buttonG);
  int value_buttonR = digitalRead(pino_buttonR);
  int value_buttonY = digitalRead(pino_buttonY);
  int value_buttonW = digitalRead(pino_buttonW);

  if (i < level) {
    if (value_buttonG == LOW) {
      flag_bG = HIGH;
      validPlayUser(pino_ledG, c);
      while(digitalRead(pino_buttonG) == LOW) {}
    } else if (value_buttonG == HIGH && flag_bG == HIGH) {
      resultado[i] = 1;
      i++;
      flag_bG = LOW;
    }

    if (value_buttonR == LOW) {
      flag_bR = HIGH;
      validPlayUser(pino_ledR, d);
      while(digitalRead(pino_buttonR) == LOW) {}
    } else if (value_buttonR == HIGH && flag_bR == HIGH) {
      resultado[i] = 2;
      i++;
      flag_bR = LOW;
    }

    if (value_buttonY == LOW) {
      flag_bY = HIGH;
      validPlayUser(pino_ledY, e);
      while(digitalRead(pino_buttonY) == LOW) {}
    } else if (value_buttonY == HIGH && flag_bY == HIGH) {
      resultado[i] = 3;
      i++;
      flag_bY = LOW;
    }

    if (value_buttonW == LOW) {
      flag_bW = HIGH;
      validPlayUser(pino_ledW, f);
      while(digitalRead(pino_buttonW) == LOW) {}
    } else if (value_buttonW == HIGH && flag_bW == HIGH) {
      resultado[i] = 4;
      i++;
      flag_bW = LOW;
    }
    delay(100);
  } else {
    for (int i = 0; i < level; i++) {
      resultado[i] = (resultado[i] - notas[i]);
      if (resultado[i] < 0) {
        resultado[i] = resultado[i] * -1;
      }
      compara = compara + resultado[i];

      if (compara > 0) {
        decrease = HIGH;
      } else {
        decrease = LOW;
      }
    }

    if (decrease == HIGH) {
      level = 0;
      decrease = LOW;

      for (i = 0; i < 5; i++) {
        digitalWrite(pino_ledG, HIGH);
        digitalWrite(pino_ledR, HIGH);
        digitalWrite(pino_ledY, HIGH);
        digitalWrite(pino_ledW, HIGH);
        tone(pino_buzzer, soundError);
        delay(50);
        digitalWrite(pino_ledG, LOW);
        digitalWrite(pino_ledR, LOW);
        digitalWrite(pino_ledY, LOW);
        digitalWrite(pino_ledW, LOW);
        noTone(pino_buzzer);
        delay(50);
      }
    } else {
      level ++;
    }

    flag = LOW;
    delay(500);
  }
  }

  delay(300);
}

void animation() {
  int leds[4] = {pino_ledG, pino_ledR, pino_ledY, pino_ledW};
  int tones[4] = {c, d, e, f};

  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], HIGH);
    tone(pino_buzzer, tones[i]);
    delay(200);
    noTone(pino_buzzer);
    digitalWrite(leds[i], LOW);
  }

  delay(500);

  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[0], HIGH);
    digitalWrite(leds[1], HIGH);
    digitalWrite(leds[2], HIGH);
    digitalWrite(leds[3], HIGH);
    tone(pino_buzzer, soundError);
    delay(200);
    noTone(pino_buzzer);
    digitalWrite(leds[0], LOW);
    digitalWrite(leds[1], LOW);
    digitalWrite(leds[2], LOW);
    digitalWrite(leds[3], LOW);

    delay(200);
  }
}

void validPlayUser(int pino_led, int tone_play) {
    digitalWrite(pino_led, HIGH);
    tone(pino_buzzer, tone_play);
    delay(500);
    noTone(pino_buzzer);
    digitalWrite(pino_led, LOW);
}