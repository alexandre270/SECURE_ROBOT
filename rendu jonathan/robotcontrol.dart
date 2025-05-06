import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:http/http.dart' as http;
import 'orientation_helper.dart';

class RobotControlPage extends StatefulWidget {
  const RobotControlPage({super.key});

  @override
  _RobotControlPageState createState() => _RobotControlPageState();
}

class _RobotControlPageState extends State<RobotControlPage> {
  String _status = "Déconnecté";
  String _currentAction = "";
  bool isPortrait = true;
  final String robotIp = 'http://192.168.0.19:12346';

  void _connectRobot() {
    setState(() {
      _status = "Connecté";
    });
    _sendRequest('connect', 'Connexion');
  }

  void _disconnectRobot() {
    setState(() {
      _status = "Déconnecté";
    });
    _sendRequest('disconnect', 'Déconnexion');
  }

  void _stop() {
    setState(() {
      _status = "S\'arrête";
    });
    _sendRequest('stop', 'Stop');
  }

  Future<void> _sendRequest(String action, [String? displayText]) async {
    if (displayText != null) {
      setState(() {
        _currentAction = displayText;
      });

      // Réinitialiser l'action après 2 secondes
      Future.delayed(const Duration(seconds: 1), () {
        if (mounted) {
          setState(() {
            _currentAction = "";
          });
        }
      });
    }

    final url = Uri.parse('$robotIp/$action');
    try {
      final response = await http.get(url);
      if (response.statusCode == 200) {
        print('Réponse du serveur : ${response.body}');
      } else {
        print('Erreur ${response.statusCode}');
      }
    } catch (e) {
      print('Erreur de connexion : $e');
    }
  }

  void _toggleOrientation() {
    SystemChrome.setPreferredOrientations(isPortrait
        ? [DeviceOrientation.landscapeLeft, DeviceOrientation.landscapeRight]
        : [DeviceOrientation.portraitUp, DeviceOrientation.portraitDown]);

    setState(() {
      isPortrait = !isPortrait;
    });
  }

  Widget _buildDirectionButton(
      String label, IconData icon, String action, String displayText) {
    return ElevatedButton(
      onPressed: () => _sendRequest(action, displayText),
      style: ElevatedButton.styleFrom(
        padding: const EdgeInsets.all(20),
        shape: const CircleBorder(),
      ),
      child: Icon(icon, size: 30),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Contrôle du Robot'),
        backgroundColor: Colors.red,
        actions: [
          IconButton(
            icon: const Icon(Icons.screen_rotation),
            onPressed: _toggleOrientation,
          ),
        ],
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text(
              'Robot : $_status',
              style: const TextStyle(fontSize: 24, fontWeight: FontWeight.bold),
            ),
            if (_currentAction.isNotEmpty) ...[
              const SizedBox(height: 10),
              Text(
                'Action : $_currentAction',
                style: const TextStyle(fontSize: 20, color: Colors.blue),
              ),
            ],
            const SizedBox(height: 30),
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                ElevatedButton(onPressed: _stop, child: const Text('Stop')),
                const SizedBox(width: 10),
                ElevatedButton(
                    onPressed: _connectRobot, child: const Text('Connexion')),
                const SizedBox(width: 10),
                ElevatedButton(
                    onPressed: _disconnectRobot, child: const Text('Déconnexion')),
              ],
            ),
            const SizedBox(height: 40),
            // Pavé directionnel
            Column(
              children: [
                // Ligne Haut
                Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    const SizedBox(width: 70),
                    _buildDirectionButton("Haut", Icons.arrow_upward,
                        "move_forward", "Avancer"),
                    const SizedBox(width: 70),
                  ],
                ),
                // Ligne Haut-Gauche, Rotation, Haut-Droite
                Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    _buildDirectionButton("Gauche", Icons.arrow_back,
                        "move_forward_left", "Gauche"),
                    _buildDirectionButton(
                        "Rotation", Icons.sync, "rotation", "Rotation"),
                    _buildDirectionButton("Droite", Icons.arrow_forward,
                        "move_forward_right", "Droite"),
                  ],
                ),
                // Ligne Milieu (Gauche/Droite)

                // Ligne Bas-Gauche, Bas, Bas-Droite
                Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    _buildDirectionButton("BasGauche", Icons.turn_left,
                        "move_backward_left", "Reculer à gauche"),
                    _buildDirectionButton("Bas", Icons.arrow_downward,
                        "move_backward", "Reculer"),
                    _buildDirectionButton("BasDroite", Icons.turn_right,
                        "move_backward_right", "Reculer à droite"),
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
