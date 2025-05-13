import 'package:flutter/material.dart';
import 'orientation_helper.dart';  // Importation pour gérer l'orientation de l'écran
import 'socket.dart';      // Importation de la classe SocketService pour la communication via sockets

class RobotControlPage extends StatefulWidget {
  const RobotControlPage({super.key});

  @override
  _RobotControlPageState createState() => _RobotControlPageState();
}

class _RobotControlPageState extends State<RobotControlPage> {
  String _status = "Déconnecté";         // Variable pour suivre l'état de la connexion du robot
  String _currentAction = "";            // Variable pour afficher l'action en cours (temporisation)

  // Fonction pour connecter le robot via socket
  void _connectRobot() async {
    await SocketService().connect(host: '192.168.0.19', port: 12345); // Connexion au robot à l'IP et au port spécifiés
    setState(() {
      _status = "Connecté";               // Mise à jour de l'état de connexion du robot
    });
    _sendRequest('connect', 'Connexion'); // Envoi de la commande de connexion au robot via socket
  }

  // Fonction pour déconnecter le robot
  void _disconnectRobot() {
    SocketService().disconnect();        // Fermeture de la connexion socket avec le robot
    setState(() {
      _status = "Déconnecté";             // Mise à jour de l'état de déconnexion du robot
    });
    _sendRequest('disconnect', 'Déconnexion'); // Envoi de la commande de déconnexion au robot
  }

  // Fonction pour arrêter le robot
  void _stop() {
    setState(() {
      _status = "S'arrête";              // Mise à jour de l'état (affichage du message "S'arrête")
    });
    _sendRequest('stop', 'Stop');        // Envoi de la commande 'stop' pour arrêter le robot
  }

  // Fonction pour envoyer une commande au robot via socket
  void _sendRequest(String action, [String? displayText]) {
    if (displayText != null) {
      setState(() {
        _currentAction = displayText;     // Mise à jour du texte de l'action en cours
      });

      // Réinitialiser l'affichage de l'action après 1 seconde
      Future.delayed(const Duration(seconds: 1), () {
        if (mounted) {
          setState(() {
            _currentAction = "";          // Réinitialisation du texte de l'action
          });
        }
      });
    }

    try {
      SocketService().send(action);       // Envoi de l'action via socket
      print('Message envoyé : $action');  // Affichage dans la console du message envoyé
    } catch (e) {
      print('Erreur d\'envoi via socket : $e'); // Gestion des erreurs d'envoi via socket
    }
  }

  // Fonction qui crée un bouton de direction pour contrôler le robot
  Widget _buildDirectionButton(
      String label, IconData icon, String action, String displayText) {
    return ElevatedButton(
      onPressed: () => _sendRequest(action, displayText),     // Envoie de la commande lorsque le bouton est pressé
      style: ElevatedButton.styleFrom(
        padding: const EdgeInsets.all(20),   // Padding autour du bouton
        shape: const CircleBorder(),         // Le bouton a une forme circulaire
      ),
      child: Icon(icon, size: 30),            // Affichage de l'icône dans le bouton
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Contrôle du Robot'),   // Titre de la barre d'applications
        backgroundColor: Colors.red,            // Couleur de la barre d'applications
        actions: [
          IconButton(
            icon: const Icon(Icons.screen_rotation),
            onPressed: () {
              setState(() {
                OrientationHelper.toggleOrientation(); // Permet de basculer entre orientation portrait/paysage
              });
            },
          ),
        ],
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),   // Espacement de 16 px autour du contenu
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,  // Alignement des éléments au centre verticalement
          children: [
            // Affichage de l'état actuel du robot (connecté, déconnecté, arrêté, etc.)
            Text(
              'Robot : $_status',
              style: const TextStyle(fontSize: 24, fontWeight: FontWeight.bold),
            ),

            // Affichage de l'action en cours, si présente
            if (_currentAction.isNotEmpty) ...[
              const SizedBox(height: 10),
              Text(
                'Action : $_currentAction',  // Affichage du texte de l'action
                style: const TextStyle(fontSize: 20, color: Colors.blue),
              ),
            ],
            const SizedBox(height: 30),  // Espacement entre les sections
            // Boutons de commande : connexion, déconnexion, arrêt
            Row(
              mainAxisAlignment: MainAxisAlignment.center,   // Alignement des boutons au centre horizontalement
              children: [
                ElevatedButton(onPressed: _stop, child: const Text('Stop')),   // Bouton pour arrêter le robot
                const SizedBox(width: 10),   // Espacement entre les boutons
                ElevatedButton(
                    onPressed: _connectRobot, child: const Text('Connexion')), // Bouton pour connecter le robot
                const SizedBox(width: 10),
                ElevatedButton(
                    onPressed: _disconnectRobot,
                    child: const Text('Déconnexion')),   // Bouton pour déconnecter le robot
              ],
            ),
            const SizedBox(height: 40),  // Espacement avant le pavé directionnel
            // Pavé directionnel avec les boutons pour déplacer le robot dans différentes directions
            Column(
              children: [
                // Ligne Haut
                Row(
                  mainAxisAlignment: MainAxisAlignment.center,   // Aligner les boutons au centre
                  children: [
                    const SizedBox(width: 70),    // Espacement avant le bouton
                    _buildDirectionButton(
                        "Haut", Icons.arrow_upward, "move_forward", "Avancer"),  // Bouton pour avancer
                    const SizedBox(width: 70),    // Espacement après le bouton
                  ],
                ),
                // Ligne milieu : gauche / rotation / droite
                Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    _buildDirectionButton("Gauche", Icons.arrow_back,
                        "move_forward_left", "Gauche"),  // Bouton pour tourner à gauche
                    _buildDirectionButton(
                        "Rotation", Icons.sync, "rotation", "Rotation"),  // Bouton pour effectuer une rotation
                    _buildDirectionButton("Droite", Icons.arrow_forward,
                        "move_forward_right", "Droite"),  // Bouton pour tourner à droite
                  ],
                ),
                // Ligne bas : reculer + diagonales
                Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    _buildDirectionButton("BasGauche", Icons.turn_left,
                        "move_backward_left", "Reculer à gauche"),  // Bouton pour reculer à gauche
                    _buildDirectionButton("Bas", Icons.arrow_downward,
                        "move_backward", "Reculer"),  // Bouton pour reculer
                    _buildDirectionButton("BasDroite", Icons.turn_right,
                        "move_backward_right", "Reculer à droite"),  // Bouton pour reculer à droite
                  ],
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }
}
