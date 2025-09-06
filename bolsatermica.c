#define analogPin A0
int redPin = 9;     
int bluePin = 11;   
int greenPin = 10;  
int resispwmPin = 6; 
int botao2Pin = 12; // pino do botão que controla o ciclo de PWM
int ligaDesligaPin = 13;
int val = 0;
int resispwmValue = 0;
int botao2State = 0;
int lastbotao2State = 0;
int pressbotao2Count = 0;
int ligaDesligaState = 0;
int lastLigaDesligaState = 0;
bool ligado = false;

void setup() { 
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);  
  pinMode(bluePin, OUTPUT); 
  pinMode(greenPin, OUTPUT); 
  pinMode(resispwmPin, OUTPUT);
  pinMode(botao2Pin, INPUT_PULLUP);
  pinMode(ligaDesligaPin, INPUT_PULLUP); 

  
  analogWrite(resispwmPin, 0); 
  analogWrite(redPin, 0);     
  analogWrite(greenPin, 0);    
  analogWrite(bluePin, 0);    
}

void loop() {

  ligaDesligaState = digitalRead(ligaDesligaPin);

  if (ligaDesligaState == LOW && lastLigaDesligaState == HIGH) {
    ligado = !ligado;
    delay(200);
  }
  lastLigaDesligaState = ligaDesligaState;

  if (!ligado) {
    analogWrite(resispwmPin, 0); 
    analogWrite(redPin, 0);     
    analogWrite(greenPin, 0);    
    analogWrite(bluePin, 0);    
    return; 
  }

  botao2State = digitalRead(botao2Pin);

  if (botao2State == LOW && lastbotao2State == HIGH) {
    pressbotao2Count++;
    
    if (pressbotao2Count == 1) {
      resispwmValue = 128;  // 50% (128 de 255)
    } else if (pressbotao2Count == 2) {
      resispwmValue = 192;  // 75% (192 de 255)
    } else if (pressbotao2Count == 3) {
      resispwmValue = 255;  // 100% (255 de 255)
    } else if (pressbotao2Count == 4) {
      resispwmValue = 64;   // 25% (64 de 255)
      pressbotao2Count = 0;
    }

    analogWrite(resispwmPin, resispwmValue);
    delay(200);
  }
  lastbotao2State = botao2State;

  //Controle das cores do LED com potenciômetro
  val = analogRead(analogPin);  
  Serial.println(val);

  if (val <= 164) {
    // Ciano
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 255);
  }
  else if (val > 164 && val <= 223) {
    // Amarelo
    analogWrite(redPin, 255);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
  }
  else if (val > 223) {
    // Vermelho
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  }  
}
