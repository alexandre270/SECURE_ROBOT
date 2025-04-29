import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: Text('Communiquer avec Qt Server'),
        ),
        body: Center(
          child: ElevatedButton(
            onPressed: _sendRequest,
            child: Text('Envoyer une requête'),
          ),
        ),
      ),
    );
  }

  Future<void> _sendRequest() async {
    final url = Uri.parse('http://<192.168.0.19>:12346'); // Remplace <ton-ip> par l'IP de ton serveur
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
}
