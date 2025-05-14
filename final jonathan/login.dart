import 'package:flutter/material.dart';
import 'package:device_info_plus/device_info_plus.dart';
import 'package:uuid/uuid.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

class LoginPage extends StatefulWidget {
  const LoginPage({super.key});

  @override
  _LoginPageState createState() => _LoginPageState();
}

class _LoginPageState extends State<LoginPage> {
  String? _deviceID;
  String? _uuid;
  bool _isLoading = true;

  @override
  void initState() {
    super.initState();
    _initializeIdentifiers();
  }

  Future<void> _initializeIdentifiers() async {
    try {
      print(" Initialisation démarrée");

      final uuid = await _getOrCreateUUID();
      print("🆔 UUID récupéré : $uuid");

      final deviceID = await _getDeviceID();
      print("📱 Device ID : $deviceID");

      setState(() {
        _uuid = uuid;
        _deviceID = deviceID;
      });

// Envoyer à l’API (tu peux changer l’URL ici)
      await _sendIdentifiers(uuid, deviceID);

      print(" Données envoyées, navigation vers /menu");
      Navigator.pushReplacementNamed(context, '/menu');
    } catch (e) {
      print(" Erreur : $e");
      setState(() {
        _isLoading = false;
      });

      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(content: Text("Erreur : $e"), backgroundColor: Colors.red),
      );
    }
  }

  Future<String> _getOrCreateUUID() async {
    final prefs = await SharedPreferences.getInstance();
    final savedUUID = prefs.getString('user_uuid');
    if (savedUUID != null) return savedUUID;

    final newUUID = const Uuid().v4();
    await prefs.setString('user_uuid', newUUID);
    return newUUID;
  }

  Future<String> _getDeviceID() async {
    final deviceInfo = DeviceInfoPlugin();

    if (Theme.of(context).platform == TargetPlatform.android) {
      final androidInfo = await deviceInfo.androidInfo;
      return androidInfo.id ?? 'unknown_android_id';
    } else if (Theme.of(context).platform == TargetPlatform.iOS) {
      final iosInfo = await deviceInfo.iosInfo;
      return iosInfo.identifierForVendor ?? 'unknown_ios_id';
    } else {
      return 'unsupported_platform';
    }
  }

  Future<void> _sendIdentifiers(String uuid, String deviceID) async {
    final url = Uri.parse('https://example.com/api/auth'); //  Remplace cette URL par la tienne

    final response = await http
        .post(
      url,
      headers: {
        'Content-Type': 'application/json',
// Tu peux ajouter une clé API ici si besoin :
// 'Authorization': 'ApiKey TA_CLE_API',
      },
      body: jsonEncode({
        'uuid': uuid,
        'device_id': deviceID,
      }),
    )
        .timeout(const Duration(seconds: 5));

    if (response.statusCode != 200) {
      throw Exception('Code ${response.statusCode} - ${response.body}');
    }

// Tu peux aussi lire un token ou une réponse ici si ton serveur envoie un JWT
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Connexion automatique')),
      body: Center(
        child: _isLoading
            ? const CircularProgressIndicator()
            : Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text('UUID : $_uuid'),
            const SizedBox(height: 10),
            Text('Device ID : $_deviceID'),
            const SizedBox(height: 20),
            ElevatedButton(
              onPressed: _initializeIdentifiers,
              child: const Text("Réessayer"),
            ),
          ],
        ),
      ),
    );
  }
}