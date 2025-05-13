import 'package:flutter/material.dart';
import 'socket.dart';

class LoginPage extends StatefulWidget {
  const LoginPage({super.key});

  @override
  _LoginPageState createState() => _LoginPageState();
}

class _LoginPageState extends State<LoginPage> {
  String _firstCode = '';
  String _secondCode = '';
  bool _stepTwo = false;

  void _validateFirstCode() {
    if (_firstCode == "1234") {
      setState(() {
        _stepTwo = true;
      });
    } else {
      _showError("Code principal incorrect");
    }
  }

  void _validateSecondCode() {
    if (_secondCode == "5678") {
      Navigator.pushReplacementNamed(context, '/menu');
    } else {
      _showError("Code secondaire incorrect");
    }
  }

  void _showError(String message) {
    ScaffoldMessenger.of(context).showSnackBar(
      SnackBar(content: Text(message), backgroundColor: Colors.red),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Authentification')),
      body: Padding(
        padding: const EdgeInsets.all(24.0),
        child: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: _stepTwo ? _buildSecondStep() : _buildFirstStep(),
          ),
        ),
      ),
    );
  }

  List<Widget> _buildFirstStep() {
    return [
      const Text("Entrez le code principal", style: TextStyle(fontSize: 18)),
      const SizedBox(height: 10),
      TextField(
        obscureText: true,
        keyboardType: TextInputType.number,
        decoration: const InputDecoration(labelText: 'Code'),
        onChanged: (value) => _firstCode = value,
      ),
      const SizedBox(height: 20),
      ElevatedButton(onPressed: _validateFirstCode, child: const Text('Suivant')),
    ];
  }

  List<Widget> _buildSecondStep() {
    return [
      const Text("Entrez le code secondaire", style: TextStyle(fontSize: 18)),
      const SizedBox(height: 10),
      TextField(
        obscureText: true,
        keyboardType: TextInputType.number,
        decoration: const InputDecoration(labelText: 'Code secondaire'),
        onChanged: (value) => _secondCode = value,
      ),
      const SizedBox(height: 20),
      ElevatedButton(onPressed: _validateSecondCode, child: const Text('Valider')),
    ];
  }
}
