import 'dart:async';
import 'dart:convert';

import 'package:http/http.dart' as http;

class GasDataController {
  late StreamController<String> _gasLevelStreamController;
  late Timer _timer;

  Stream<String> get gasLevelStream => _gasLevelStreamController.stream;

  GasDataController() {
    _gasLevelStreamController = StreamController<String>();
    _startPolling();
  }

  void _startPolling() {
    _timer = Timer.periodic(const Duration(seconds: 5), (timer) {
      _fetchLatestGasData();
    });
  }

  void _fetchLatestGasData() async {
    try {
      final response =
          await http.get(Uri.parse('http://192.168.216.239:8080/api/get-gas'));
      if (response.statusCode == 200) {
        final gasLevel = jsonDecode(response.body)['gas_level'].toString();
        _gasLevelStreamController.add(gasLevel);
      } else {
        throw Exception('Failed to load gas data');
      }
    } catch (e) {
      // ignore: avoid_print
      print('Error fetching gas data: $e');
    }
  }

  void dispose() {
    _gasLevelStreamController.close();
    _timer.cancel();
  }
}
