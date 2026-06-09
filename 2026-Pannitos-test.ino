// ===== Definición de pines por letra =====
int P[]  = {14,15,16,17,18,19,20};
int A[]  = {2,3,4,5,6,7};
int N1[] = {8,9,10,11,12,13};
int N2[] = {22,24,26,28,30,32};
int I[]  = {34,36,38};
int T[]  = {40,42,44,46,48,50,52};
int O[]  = {23,25,27,29,31,33};
int AP[] = {21};
int S[]  = {35,37,39,41};

// ===== Vector completo en orden correcto =====
int* letra[] = {P, A, N1, N2, I, T, O, AP, S};
// ===== Cantidad de pines por letra =====
int segmento[] =  {7, 6,  6,  6, 3, 7, 6,  1, 4};
// ===== Número total de letras =====
int totalLetras = 9;

void setup() {
  // Pines digitales 2 al 53
  for (int l = 0; l < totalLetras; l++) {
    for (int s = 0; s < segmento[l]; s++) {
      pinMode(letra[l][s], OUTPUT);      
    }
  }
  all_off();

  // Pines analógicos A0 al A15
  for (int pin = A0; pin <= A15; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }
}

void loop() {
  secuencial_letras_y_segmentos();
  all_off();
}

void secuencial_letras_y_segmentos(){
  for (int l = 0; l < totalLetras; l++) {
    for (int s = 0; s < segmento[l]; s++) {
      digitalWrite(letra[l][s], HIGH);        
      delay(5); // velocidad de aparición
    }      
  }
}
// 7. secuencia todos apagados
void all_off(){
  for (int l = 0; l < totalLetras; l++) {
    for (int s = 0; s < segmento[l]; s++) {      
      digitalWrite(letra[l][s], LOW);
    }
  }
}