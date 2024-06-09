#include<Wire.h>

/*
Programme arduino pour obtenir une mesure d'angle à partir du module MPU
6050 équipé d'une puce GY521.
Pour montage sur rack de panneaux solaires et mesure de l'orientation des racks
par rapport à l'horizontale locale.
Angle = 0   ---->   racks de panneaux à l'horizontale.
Communication I2C: lecture directe du registre.
 */

//DECLARATION DES VARIABLES
//Adresse I2C du module MPU6050
const int MPU=0x68;

int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
//AcX, AcY, AcZ: mesure d'accélération sur l'axe concerné
//GyX, GyY, GyZ: mesure du gyroscope sur l'axe concerné

float AngleX;
//Résultat du calcul de l'orientation du module sur l'axe X

float OffsetMesureAcX=3000.0;
//Correction de la valeur mesuree sur les erreurs relevees en conception.

void  setup(){
  //setup I2C pour connexion au module MPU6050
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  //Initialisation de la liaison série arduino/pc
  Serial.begin(9600);
}

void  loop(){
  beginTransmission_I2C_MPU6050();

  readingDatas_I2C_MPU6050();
  
  //si reception du caractere a de la liaison serie, renvoi des donnees
  //par liaison serie, sinon, retour sur un cycle de lecture des donneess.
  if(Serial.available()>0){
    if(Serial.read() == 'a'){
      //valeur reçue de Serial.read = char
      Serial.print(AcX);Serial.print("|");Serial.print(AcY);Serial.print("|");Serial.print(AcZ);Serial.print("|");
      Serial.print(GyX);Serial.print("|");Serial.print(GyY);Serial.print("|");Serial.println(GyZ);
      AngleX=AcX*90.0/(20000.0-OffsetMesureAcX);
      Serial.print("Angle X: ");Serial.println(AngleX);
    }
  }
  endTransmission_I2C_MPU6050();
}

void beginTransmission_I2C_MPU6050() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
}

void readingDatas_I2C_MPU6050() {
  //               @   qty stop
  Wire.requestFrom(MPU,12,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  GyX=Wire.read()<<8|Wire.read();
  GyY=Wire.read()<<8|Wire.read();
  GyZ=Wire.read()<<8|Wire.read();
}
void endTransmission_I2C_MPU6050() {
  Wire.endTransmission(true); 
}
