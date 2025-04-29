import 'package:flutter/material.dart';
import 'menu.dart'; // Importation du menu principal
import 'robotcontrol.dart'; // Importation de la page de contrôle du robot
import 'telemetrie.dart'; // Importation de la page de télémétrie

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,  // Désactive l'indicateur DEBUG
      title: 'SecuRobot Controller',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      initialRoute: '/',  // Définit la page de menu comme écran d’accueil
      routes: {
        '/': (context) => const MenuPage(),  // Accueil
        '/robot': (context) => const RobotControlPage(),  // Page de contrôle du robot
        '/telemetry': (context) => const TelemetryPage(),

      },
    );
  }
}
