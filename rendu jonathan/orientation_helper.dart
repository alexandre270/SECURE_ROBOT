import 'package:flutter/services.dart';

class OrientationHelper {
  static bool isPortrait = true;

  static void toggleOrientation() {
    if (isPortrait) {
      SystemChrome.setPreferredOrientations([
        DeviceOrientation.landscapeLeft,
        DeviceOrientation.landscapeRight,
      ]);
    } else {
      SystemChrome.setPreferredOrientations([
        DeviceOrientation.portraitUp,
        DeviceOrientation.portraitDown,
      ]);
    }
    isPortrait = !isPortrait;
  }
}
