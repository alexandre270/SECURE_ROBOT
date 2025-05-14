import 'dart:io'; // Importation de la bibliothèque pour la gestion des sockets

// Définition du type de fonction pour gérer les messages reçus
typedef MessageCallback = void Function(String);

/// Classe de service pour la gestion d'une connexion Socket.
class SocketService {
  // Instance unique du service (Singleton pattern)
  static final SocketService _instance = SocketService._internal();

  // Factory pour retourner l'instance unique de SocketService
  factory SocketService() => _instance;

  // Constructeur privé pour empêcher l'instanciation directe
  SocketService._internal();

  // Socket pour la connexion avec le serveur
  Socket? _socket;

  // Callback qui sera appelé lorsqu'un message est reçu
  MessageCallback? onMessageReceived;

  /// Connexion au serveur via un Socket.
  ///
  /// Cette méthode essaie de se connecter au serveur en utilisant l'adresse `host` et le `port` spécifiés.
  Future<void> connect({required String host, required int port}) async {
    try {
      // Tentative de connexion au serveur
      _socket = await Socket.connect(host, port);
      print(" Connecté au serveur $host:$port");

      // Écoute les données envoyées par le serveur
      _socket!.listen(
            (data) {
          // Convertit les données reçues en texte
          final message = String.fromCharCodes(data);
          print(" Message reçu: $message");

          // Si un callback est défini, il est appelé avec le message reçu
          if (onMessageReceived != null) {
            onMessageReceived!(message);
          }
        },
        onError: (err) {
          // Si une erreur survient, on l'affiche et on ferme la connexion
          print(" Erreur socket: $err");
          _socket?.destroy(); // Ferme la socket en cas d'erreur
        },
        onDone: () {
          // Si la connexion est fermée par le serveur, on le notifie
          print(" Connexion fermée par le serveur.");
          _socket?.destroy(); // Ferme la socket proprement
        },
      );
    } catch (e) {
      // Si la connexion échoue, on affiche l'erreur
      print("❗ Impossible de se connecter: $e");
    }
  }

  /// Envoie un message au serveur.
  ///
  /// Cette méthode écrit le message sur la socket pour l'envoyer au serveur.
  void send(String message) {
    _socket?.write(message); // Envoie le message via la socket
  }

  /// Ferme la connexion socket.
  ///
  /// Cette méthode ferme la socket proprement en fermant la connexion.
  void disconnect() {
    _socket?.close(); // Ferme la connexion de la socket
  }
}
