#include <Servo.h> 
Servo servo;

// Déclaration des constantes
const int pinEMG = A0;      // Pin sur lequel est connecté le capteur EMG
const int seuil = 700;     // Seuil pour déclencher un changement d'état
const unsigned long tau = 1000;     // Délai d'attente en millisecondes à définir
int etat = 0;       // Etat initial, 0 = inactif, 1 = actif

// init bouton 
const int buttonPin = 8; // Pin où le bouton est connecté
int buttonState = 0;     // Variable pour lire l'état du bouton

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Configurer le pin avec pull-up interne
  Serial.begin(9600); // Initialiser la communication série
  servo.attach(5); // connexion servo pin 5 
  servo.write(0);
}

void loop() {
  buttonState = digitalRead(buttonPin); // Lire l'état du bouton
  
  // Le bouton est pressé v1
  if (buttonState == LOW) {
    Serial.println("pressé");

    int valeurEMG = analogRead(pinEMG);   // Lecture de la valeur du capteur EMG
      Serial.println(valeurEMG); 

    if (valeurEMG > seuil ) {    //seuil dépassé + temps d'attente respecté
      if (etat == 0){   //conditionne le changement d'état
        etat = 1;   
        servo.write(180);
        delay(tau);     //attente pour ne pas bouclé sur la même contraction
      }
      else if (etat == 1){   //conditionne le changement d'état
        etat = 0;   
        servo.write(0);
        delay(tau);     //attente pour ne pas bouclé sur la même contraction
      }
  }
    
  } else { //bouton relaché v2
    Serial.println("relaché");

    int valeurEMG = analogRead(pinEMG);   // Lecture de la valeur du capteur EMG
    Serial.println(valeurEMG); 

    while(valeurEMG > seuil){
      servo.write(180);
      etat=1;
      valeurEMG = analogRead(pinEMG);
      Serial.println(valeurEMG);     
    }
    etat=0;
    servo.write(0);
  }
  
  delay(50); // Petit délai pour éviter les rebonds
}