import 'package:flutter/material.dart';

class TelemetryPage extends StatefulWidget {
  const TelemetryPage({super.key});

  @override
  _TelemetryPageState createState() => _TelemetryPageState();
}

class _TelemetryPageState extends State<TelemetryPage> {
  double temperature = 46.5; // Température en degrés Celsius
  double inclination = 5.0; // Inclinaison en degrés
  double distance = 1.5; // Distance en mètres

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Télémétrie'),
        backgroundColor: Colors.blue,
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            _buildTelemetryCard('Température', temperature, '°C', Icons.thermostat),
            const SizedBox(height: 20),
            _buildTelemetryCard('Inclinaison du sol', inclination, '°', Icons.landscape),
            const SizedBox(height: 20),
            _buildTelemetryCard('Distance du robot', distance, 'm', Icons.straighten),
          ],
        ),
      ),
    );
  }

  // Widget pour afficher chaque donnée sous forme de carte
  Widget _buildTelemetryCard(String title, double value, String unit, IconData icon) {
    return Card(
      elevation: 5,
      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(10)),
      child: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Row(
          mainAxisAlignment: MainAxisAlignment.spaceBetween,
          children: [
            Icon(icon, size: 40, color: Colors.blue),
            Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(title, style: const TextStyle(fontSize: 20, fontWeight: FontWeight.bold)),
                Text('$value $unit', style: const TextStyle(fontSize: 18)),
              ],
            ),
          ],
        ),
      ),
    );
  }
}
