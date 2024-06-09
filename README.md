# AngleDetection_GY521
Détection d'angle en utilisant un module accéléromètre MPU6050 GY521

Matériel nécessaire:
- carte type arduino
- un module MPU6050 avec GY521 (accéléromètre/gyroscope, en liaison I2C avec la carte arduino).

Connexions:
Le module est connecté à la carte arduino par les broches I2C (voir pinout de la carte arduino utilisée).
Il est alimenté en 5Vcc, par Arduino.
La carte arduino est connecté à l'ordinateur par le port USB.

Le code:
Librairie utilisée: Wire pour gestion du bus I2C.
La données sont lues directement sur la carte.

La température peut être lue en ajoutant une lecture de 2 octet ligne 65 et ajouter la 
lecture de température après les informations du gyroscope Z.
