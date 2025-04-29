import 'package:flutter/material.dart'; // Importation du package pour créer l'interface utilisateur
import 'package:flutter/services.dart'; // Permet de gérer l'orientation de l'écran
import 'package:flutter_joystick/flutter_joystick.dart'; // Bibliothèque pour le joystick de contrôle
import 'package:http/http.dart' as http; // Importation de la bibliothèque HTTP

const double ballSize = 20.0; // Définition de la taille de la balle (robot)
const double step = 10.0; // Déplacement du robot (balle) à chaque mouvement du joystick

// Classe principale de la page de contrôle du robot
class RobotControlPage extends StatefulWidget {
  const RobotControlPage({super.key});

  @override
  _RobotControlPageState createState() => _RobotControlPageState();
}

// Classe d'état qui gère l'interaction avec le robot et l'affichage
class _RobotControlPageState extends State<RobotControlPage> {
  String _status = "Déconnecté"; // État initial du robot
  double _x = 100, _y = 100; // Position initiale de la balle
  bool isPortrait = true; // Indicateur du mode d'affichage (portrait/paysage)
  JoystickMode _joystickMode = JoystickMode.all; // Mode du joystick (déplacement dans toutes les directions)
  final String robotIp = 'http://192.168.0.19:12346'; // Remplace <ton-ip> par l'IP de ton serveur

  // Fonction pour connecter le robot
  void _connectRobot() {
    setState(() {
      _status = "Connecté"; // Met à jour le statut
    });
    _sendRequest('connect');
  }

  // Fonction pour déconnecter le robot
  void _disconnectRobot() {
    setState(() {
      _status = "Déconnecté"; // Met à jour le statut
    });
    _sendRequest('disconnect');
  }

  // Fonction pour arrêter le robot
  void _stop() {
    setState(() {
      _status = "S'arrête"; // Met à jour le statut
    });
    _sendRequest('stop');
  }

  // Fonction pour envoyer des requêtes HTTP au serveur
  Future<void> _sendRequest(String action) async {
    final url = Uri.parse('$robotIp/$action'); // Crée l'URL pour l'action donnée
    try {
      final response = await http.get(url); // Envoie la requête GET
      if (response.statusCode == 200) {
        print('Réponse du serveur : ${response.body}');
      } else {
        print('Erreur ${response.statusCode}');
      }
    } catch (e) {
      print('Erreur de connexion : $e');
    }
  }

  // Fonction pour changer l'orientation de l'écran (portrait/paysage)
  void _toggleOrientation() {
    SystemChrome.setPreferredOrientations(isPortrait
        ? [DeviceOrientation.landscapeLeft, DeviceOrientation.landscapeRight] // Passe en mode paysage
        : [DeviceOrientation.portraitUp, DeviceOrientation.portraitDown]); // Passe en mode portrait

    setState(() {
      isPortrait = !isPortrait; // Bascule entre les modes
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Contrôle du Robot'), // Titre de l'application
        backgroundColor: Colors.red, // Couleur de la barre d'application
        actions: [
          IconButton(
            icon: const Icon(Icons.screen_rotation), // Icône pour changer l'orientation
            onPressed: _toggleOrientation, // Appel de la fonction de changement d'orientation
          ),
        ],
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0), // Ajout de marges
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center, // Alignement vertical
          crossAxisAlignment: CrossAxisAlignment.center, // Alignement horizontal
          children: [
            Text(
              'Robot : $_status', // Affichage du statut du robot
              style: const TextStyle(fontSize: 24, fontWeight: FontWeight.bold), // Style du texte
            ),
            const SizedBox(height: 40), // Espacement
            Row(
              mainAxisAlignment: MainAxisAlignment.center, // Alignement des boutons
              children: [
                ElevatedButton(onPressed: _stop, child: const Text('Stop')), // Bouton pour arrêter
                const SizedBox(width: 10),
                ElevatedButton(onPressed: _connectRobot, child: const Text('Connexion')), // Bouton de connexion
                const SizedBox(width: 10),
                ElevatedButton(onPressed: _disconnectRobot, child: const Text('Déconnexion')), // Bouton de déconnexion
              ],
            ),
            const SizedBox(height: 40),
            Expanded(
              child: Stack(
                children: [
                  Ball(_x, _y), // Affichage de la balle représentant le robot
                  Align(
                    alignment: const Alignment(0, 0.8), // Position du joystick
                    child: Joystick(
                      mode: _joystickMode, // Mode de joystick
                      listener: (details) {
                        setState(() {
                          _x += step * details.x; // Mise à jour de la position X du robot
                          _y += step * details.y; // Mise à jour de la position Y du robot
                        });
                        _sendRequest('move'); // Envoie la requête lors du mouvement du joystick
                      },
                    ),
                  ),
                ],
              ),
            ),
          ],
        ),
      ),
    );
  }
}

// Classe représentant la balle (robot) qui se déplace selon les coordonnées
class Ball extends StatelessWidget {
  final double x, y; // Position actuelle de la balle
  const Ball(this.x, this.y, {super.key});

  @override
  Widget build(BuildContext context) {
    return Positioned(
      left: x, // Position horizontale
      top: y, // Position verticale
      child: Container(
        width: ballSize, // Largeur de la balle
        height: ballSize, // Hauteur de la balle
        decoration: const BoxDecoration(
          shape: BoxShape.circle, // Forme circulaire
          color: Colors.redAccent, // Couleur rouge
          boxShadow: [BoxShadow(color: Colors.black12, spreadRadius: 2, blurRadius: 3, offset: Offset(0, 3))], // Ombre pour effet visuel
        ),
      ),
    );
  }
}