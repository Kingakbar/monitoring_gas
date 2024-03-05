import 'package:flutter/material.dart';
import 'package:monitoringgas/controller/gas_data.dart';

class HomePage extends StatefulWidget {
  // ignore: use_super_parameters
  const HomePage({Key? key}) : super(key: key);

  @override
  // ignore: library_private_types_in_public_api
  _HomePageState createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  final GasDataController _gasDataController = GasDataController();

  @override
  void dispose() {
    _gasDataController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Colors.deepPurple,
        centerTitle: true,
        title: const Text(
          'Monitoring Gas',
          style: TextStyle(
            color: Colors.white,
          ),
        ),
      ),
      body: Center(
        child: StreamBuilder<String>(
          stream: _gasDataController.gasLevelStream,
          builder: (context, snapshot) {
            if (snapshot.hasData) {
              return Text(
                '${snapshot.data} PPM',
                style: const TextStyle(
                  fontSize: 30,
                  fontWeight: FontWeight.bold,
                ),
              );
            } else if (snapshot.hasError) {
              return Text('Error: ${snapshot.error}');
            }
            return const CircularProgressIndicator();
          },
        ),
      ),
    );
  }
}
