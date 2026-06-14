const unsigned long SEIS_HORAS = 6UL * 60UL * 60UL * 1000UL; // 21,600,000 ms
unsigned long tiempoInicio;
const uint16_t tiempo_de_barrido_1 = 1*1000;
const uint16_t tiempo_de_barrido_2 = 2*1000;
const uint16_t tiempo_de_barrido_3 = 3*1000;
const uint16_t tiempo_de_barrido_5 = 5*1000;

// ===== Definición de pines por letra =====
int P[]  = {14,15,16,17,18,19,20};
int A[]  = {2,3,4,5,6,7};
int N1[] = {8,9,10,11,12,13};
int N2[] = {32,30,28,26,24,22};
int I[]  = {34,36,38};
int T[]  = {40,46,48,50,52,42,44};
int O[]  = {27,25,23,33,31,29};
int AP[] = {21};
int S[]  = {41,39,37,35};

// ===== Vector completo en orden correcto =====
int* letra[] = {P, A, N1, N2, I, T, O, AP, S};
// ===== Cantidad de pines por letra =====
int segmento[] =  {7, 6,  6,  6, 3, 7, 6,  1, 4};
// ===== Número total de letras =====
uint8_t totalLetras = 9;


// ===== SETUP =====
void setup() {
  tiempoInicio = millis();  // Guarda el instante de arranque
  // Configurar todos los pines como salida
  for (int l = 0; l < totalLetras; l++) {
    for (int s = 0; s < segmento[l]; s++) {
      pinMode(letra[l][s], OUTPUT);      
    }
  }
  all_off();
  tiempoInicio=millis();
}

// ===== LOOP =====
void loop() {
  //temporizador de 6 horas
  if (millis() - tiempoInicio >= SEIS_HORAS) {
    all_off();      
  }
  else{
    // funciones de secuencias        
    all_on(); 
    delay(1000);
    all_off();      
    delay(1000);
    all_on(); 
    delay(1000);
    all_off(); 
    delay(1000);

    llenado_secuencial_letras_right();
    delay(1000);
    all_off(); 
    delay(1000);

    llenado_secuencial_letras_left();
    delay(1000);
    all_off(); 
    delay(1000);
 

    secuencial_letras_right();
    //delay(tiempo_de_barrido_1/totalLetras);
    all_off(); 
    secuencial_letras_left();
    //delay(tiempo_de_barrido_1/totalLetras);
    all_off(); 


    llenado_secuencial_letras_y_segmentos_right();
    delay(1000);
    all_off(); 

    llenado_secuencial_letras_y_segmentos_left();
    delay(1000);
    all_off();

    //secuencial_letras_y_segmentos_right();
    //delay(1000);
    //all_off(); 

    //secuencial_letras_y_segmentos_left();
    //delay(1000);
    //all_off(); 

    //choque();
  }
}

// 1. llenado secuancial de letras derecha
void llenado_secuencial_letras_right(){
  for (int l = 0; l < totalLetras; l++) {
    for (int s = 0; s < segmento[l]; s++) {
      digitalWrite(letra[l][s], HIGH);        
    }
    delay(tiempo_de_barrido_3/totalLetras); // mantener encendido
  }
}

// 2. llenado secuancial de letras izquierda
void llenado_secuencial_letras_left(){
  for (int l = totalLetras - 1; l >= 0; l--) {
    for (int s = 0; s < segmento[l]; s++) {
      digitalWrite(letra[l][s], HIGH);        
    }
    delay(tiempo_de_barrido_3/totalLetras); // mantener encendido
  }
}

// 3. secuancial de letras derecha
void secuencial_letras_right(){
  for (int l = 0; l < totalLetras; l++) {
    for (int s = 0; s < segmento[l]; s++) {
      digitalWrite(letra[l][s], HIGH);               
    }
    if (l>0){
      for (int s = 0; s < segmento[l-1]; s++) {
        digitalWrite(letra[l-1][s], LOW);               
      }
    }       
    delay(tiempo_de_barrido_3/totalLetras); // mantener encendido
  }
  
}

// 4. secuancial de letras izquierda
void secuencial_letras_left(){
  for (int l = totalLetras - 1; l >= 0; l--) {
    for (int s = 0; s < segmento[l]; s++) {
      digitalWrite(letra[l][s], HIGH);        
    }
    if (l<(totalLetras-1)){
      for (int s = 0; s < segmento[l+1]; s++) {
        digitalWrite(letra[l+1][s], LOW);               
      }
    }
    delay(tiempo_de_barrido_3/totalLetras); // mantener encendido
  }
  
}

// 5. llenado secuancial de letras y segmentos
void llenado_secuencial_letras_y_segmentos_right(){
  for (int l = 0; l < totalLetras; l++) {
    for (int s = 0; s < segmento[l]; s++) {
      digitalWrite(letra[l][s], HIGH);        
      delay(tiempo_de_barrido_3/(46)); // velocidad de aparición
    }      
  }
}

// 6. llenado secuancial de letras y segmentos izquierda
void llenado_secuencial_letras_y_segmentos_left(){
  for (int l = totalLetras - 1; l >= 0; l--){
    for (int s = segmento[l] - 1; s >= 0; s--){
      digitalWrite(letra[l][s], HIGH);        
      delay(tiempo_de_barrido_3/(46)); // velocidad de aparición
    }      
  }
}

// 7. secuancial de letras y segmentos
void secuencial_letras_y_segmentos_right(){
  uint8_t ultimaLetra = 0;
  uint8_t ultimoSegmento = 0;
  for (int l = 0; l < totalLetras; l++) {
    for (int s = 0; s < segmento[l]; s++) {
      digitalWrite(letra[l][s], HIGH);              
      if (l != 0 || s != 0) {
        digitalWrite(letra[ultimaLetra][ultimoSegmento], LOW);
      }
      delay(tiempo_de_barrido_5/(46)); // velocidad de aparición
      ultimaLetra = l;
      ultimoSegmento = s;
    }     
  }
}

// 8. secuancial de letras y segmentos
void secuencial_letras_y_segmentos_left(){
  uint8_t ultimaLetra = 0;
  uint8_t ultimoSegmento = 0;
  for (int l = totalLetras - 1; l >= 0; l--){
    for (int s = segmento[l] - 1; s >= 0; s--){
      digitalWrite(letra[l][s], HIGH);              
      if (l != totalLetras - 1 || s != segmento[l] - 1) {
        digitalWrite(letra[ultimaLetra][ultimoSegmento], LOW);
      }
      delay(tiempo_de_barrido_5/(46)); // velocidad de aparición
      ultimaLetra = l;
      ultimoSegmento = s;
    }     
  }
}

// 9. choque
void choque(){
  all_on();
  uint8_t ultimaLetra = 0;
  uint8_t ultimoSegmento = 0;
  uint8_t cuenta = 0;
  bool salir = false;

  for (int c = 0; c < 46; c++){
    salir = false;
    cuenta = 0;
    ultimaLetra = 0;
    ultimoSegmento = 0;
    for (int l = 0; l < totalLetras && !salir; l++) {
      for (int s = 0; s < segmento[l]; s++) {
        cuenta++;
        if (cuenta>c) {
          digitalWrite(letra[l][s], LOW);
          digitalWrite(letra[ultimaLetra][ultimoSegmento], LOW); 
          salir = true;
          break;  // Sale de este for
        }
 
        digitalWrite(letra[l][s], HIGH);              
        if (l != 0 || s != 0) {
          digitalWrite(letra[ultimaLetra][ultimoSegmento], LOW);
        }
        delay(tiempo_de_barrido_2/(46)); // velocidad de aparición
        ultimaLetra = l;
        ultimoSegmento = s;
      }     
    }
  }  
}

// 10. secuencia todos encendidos
void all_on(){
  for (int l = 0; l < totalLetras; l++) {
    for (int s = 0; s < segmento[l]; s++) {      
      digitalWrite(letra[l][s], HIGH);
    }
  }
}

// 11. secuencia todos apagados
void all_off(){
  for (int l = 0; l < totalLetras; l++) {
    for (int s = 0; s < segmento[l]; s++) {      
      digitalWrite(letra[l][s], LOW);
    }
  }
}