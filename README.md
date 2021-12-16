# Interface Homme-Machine

## Lyre ↔ Web

![Interface Web](https://media.discordapp.net/attachments/645648108629524557/920974722391502858/unknown.png?width=960&height=438 "Interface Web")

Pour se faire, nous avons utilisé la liaison série DMX512 avec le matériel suivant : 

- Carte ESP8266
- Adaptateur DMX Grove
- Lyre de spectacle ClubSpot 150

En raison de la forte difficulté à contrôler la lyre grâce aux moyens fournis par le constructeur, nous avons décidé de créer un site web permettant de le contrôler à distance (voir ci-dessus pour le visuel)

### Adressage

Pour l'instant, une seule addresse est disponible pour s'y connecter : c'est l'adresse **A001**

### Comment l'utiliser?

- #### Mouvements PAN et TILT

Afin de bouger la lyre de spectacle, vous devez bouger le joystick (rond rouge présent sur la page) dans la direction que vous voulez.

- #### Changement de couleurs

Afin de changer les couleurs qui s'affichent sur la lyre, vous devez cliquer sur les boutons ayant la couleur que vous souhaitez afficher.

- #### Luminosité

Afin de changer la luminosité de la lyre de spectacle, vous devez choisir grâce au potentiomètre affiché sur l'écran la valeur que vous souhaitez.

### Difficultés rencontrées

Lors de la première phase de création, la plus grande difficulté fût de trouver le moyen de faire communiquer notre site web vers la lyre. Pour cela, nous avons utilisé les bibliothèques suivantes :

- ESP8266WiFi.h (Afin de se connecter à un réseau wifi)
- ESP8266WebServer.h (Afin de créer notre propre serveur web)
- ESPDMX.h (Puisque la bibliothèque `DMXSimple` qui était proposée n'était pas compatible avec la carte que nous utilisions)

Ensuite, nous voulions faire bouger notre lyre avec un moyen que la plupart des personnes pourraient utiliser, pour se faire nous avions commencé à créer un potentiomètre définissant les valeurs de `PAN` et de `TILT` cependant ce moyen n'était pas très intuitif. Alors, nous avons décidé de partir sur un joystick.

### Foncionnement de liaison série DMX512

Afin de communiquer avec notre lyre, nous devions utiliser le protocole DMX 16 bits. Pour se faire, nous avions à notre disposition plusieurs canaux représentant le `PAN`, le `TILT` et d'autres fonctionnalités suivit d'un nombre entre `0` et `255` représentant la valeur associée au canal.

![Tableau1](https://media.discordapp.net/attachments/645648108629524557/920989882342600764/unknown.png "Tableau 1")
![Tableau2](https://media.discordapp.net/attachments/645648108629524557/920990201235509288/unknown.png "Tableau 2")
![Tableau3](https://media.discordapp.net/attachments/645648108629524557/920990457264226334/unknown.png "Tableau 3")
