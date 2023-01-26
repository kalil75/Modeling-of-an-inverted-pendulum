//inputs
int pinInput1 = 6; // Commande de sens moteur, Input 1
int pinInput2 = 7; // Commande de sens moteur, Input 2
int pinPower = 9; // Commande de vitesse moteur, Output Enabled1
int encoderPinA = 2;//compteur 1
int encoderPinB = 3;//compteur 2
//init counter :
int encoder0Pos = 0; //start position=0
int A_set;
int B_set;
//ordre or consigne
int angle_ticks=0; //easier to enslave in ticks 
un nombre entier
// init calculs asservissement PID
int erreur = 0; //erreur
float erreurPrecedente = 0;
float somme_erreur = 0;
//PID controller constants
float kp = 280; // Coefficient proportionnel performances
float ki = 0; //5.5; // Coefficient intégrateur
float kd = 0;//100; // Coefficient dérivateur
/* Routine d’initialisation */
void setup() {
pinMode(pinPower, OUTPUT); // output commande moteur
pinMode( pinInput1, OUTPUT );
pinMode( pinInput2, OUTPUT );
pinMode(encoderPinA, INPUT); //output encodeur
pinMode(encoderPinB, INPUT);
digitalWrite(encoderPinA, HIGH); // Internal resistor arduino ON
digitalWrite(encoderPinB, HIGH); // Internal resistor arduino ON
// Interruption of encoder A at output 0 (pin 2)
attachInterrupt(0, doEncoderA, CHANGE);
}
void loop(){
erreur = angle_ticks - (encoder0Pos*360)/400;
// Calculation of current motor speed
somme_erreur += erreur;
// Calculation of current motor speed
int vitMoteur=kp*erreur+kd*(erreur-erreurPrecedente)+ki*(somme_erreur);
erreurPrecedente = erreur; // Overwrites the previous error with the new error
// Normalisation et contrôle  moteur
if(vitMoteur > 255) vitMoteur = 255;
else if (vitMoteur < -255) vitMoteur = -255;
Tourner (vitMoteur);
}
// Interrupt called at all state changes of A
void doEncoderA(){
A_set = digitalRead(encoderPinA);
B_set = digitalRead(encoderPinB);
if (A_set == B_set) {
encoder0Pos--;
}
else {
encoder0Pos++;
}
}
//Function called to control the motor
void Tourner( int rapportCyclique ){
if (rapportCyclique > 0) {
digitalWrite( pinInput1, LOW );
digitalWrite( pinInput2, HIGH );
}
else {
digitalWrite( pinInput1, HIGH );
digitalWrite( pinInput2, LOW );
rapportCyclique = -rapportCyclique;
}
analogWrite( pinPower, rapportCyclique);
}
