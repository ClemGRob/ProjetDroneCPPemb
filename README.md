# ProjetDroneCPPemb
Ce projet utilise la stéganographie ainsi que le protocole MQTT. Son objectif est de récupérer une image prise par un drone en vol et de retirer les coordonnées associées à cette image de manière à les utiliser dans un autre contexte.
## L'équipe Base
Nous avons créé un programme graphique en C++ avec QtDesign, qui se connecte au broker mqtt://broker.emqx.io:1883 et s'abonne au topic /ynov/bordeaux/ProjetDroneCPPemb avec une qualité de service de niveau 2 (QoS 2).
## L'équipe Drone
Nous avons développé un programme console en C++ avec Qt qui charge le fichier DroneIMG37337.png, y ajoute les coordonnées GPS 37°42'41.9"S 144°59'33.0"E via un algorithme différent de steghide.
