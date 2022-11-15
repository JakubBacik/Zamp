#define ROTATE_SPEED     0.5
/*
 *  Przykładowy zestaw poleceń
 */
  Rotate Podstawa1 ROTATE_SPEED 90
  Pause 1000 /* Zawieszenie na 1 sek. */
  Set Podstawa3 -8 -8 2
  Move Podstawa1 0.05 5
  Pause 1000 /* Zawieszenie na 1 sek. */
  Set Podstawa3 8 -8 2
  Move Podstawa2 0.05 5
  Pause 1000 /* Zawieszenie na 1 sek. */
  Set Podstawa3 8 8 2
  Move Podstawa1 -0.05 5
  Pause 1000 /* Zawieszenie na 1 sek. */
  Set Podstawa3 -8 -8 -2
  Rotate Podstawa1 -0.5 90
  Pause 1000 /* Zawieszenie na 1 sek. */


