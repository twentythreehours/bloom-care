import 'dart:async';

import 'package:flutter/material.dart';

import 'app-backend-code/app_backend.dart';

void main() {
  runApp(const BloomCareApp());
}

class BloomCareApp extends StatelessWidget {
  const BloomCareApp({super.key});

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      debugShowCheckedModeBanner: false,
      home: BackendDemoPage(),
    );
  }
}

class BackendDemoPage extends StatefulWidget {
  const BackendDemoPage({super.key});

  @override
  State<BackendDemoPage> createState() => _BackendDemoPageState();
}

class _BackendDemoPageState extends State<BackendDemoPage> {
  late final BloomCareBackend _backend;
  StreamSubscription<BackendSnapshot>? _subscription;
  BackendSnapshot? _snapshot;

  @override
  void initState() {
    super.initState();

    _backend = BloomCareBackend(
      dataSource: MockSensorDataSource(),
      repository: InMemorySensorDataRepository(),
    );

    _subscription = _backend.snapshots.listen((snapshot) {
      if (!mounted) return;
      setState(() => _snapshot = snapshot);
    });

    unawaited(_backend.start());
  }

  @override
  void dispose() {
    unawaited(_subscription?.cancel());
    unawaited(_backend.dispose());
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    final data = _snapshot?.latestData;
    final flower = _snapshot?.flowerParameters;

    return Scaffold(
      appBar: AppBar(title: const Text('Bloom Care backend demo')),
      body: Padding(
        padding: const EdgeInsets.all(24),
        child: _snapshot == null
            ? const Center(child: CircularProgressIndicator())
            : ListView(
                children: [
                  if (_snapshot!.errorMessage != null)
                    Text(
                      _snapshot!.errorMessage!,
                      style: const TextStyle(color: Colors.red),
                    ),
                  Text('Heartbeat: ${data?.heartbeat ?? '-'} bpm'),
                  Text('SpO2: ${data?.spo2 ?? '-'}%'),
                  Text(
                    'Skin temperature: '
                    '${data?.skinTemp.toStringAsFixed(1) ?? '-'} C',
                  ),
                  Text('Activity: ${data?.activity ?? '-'}'),
                  const SizedBox(height: 20),
                  Text(
                    'Petal openness: '
                    '${flower?.petalOpenness.toStringAsFixed(2) ?? '-'}',
                  ),
                  Text(
                    'Saturation: '
                    '${flower?.saturation.toStringAsFixed(2) ?? '-'}',
                  ),
                  Text(
                    'Hue shift: '
                    '${flower?.hueShiftDegrees.toStringAsFixed(1) ?? '-'}',
                  ),
                ],
              ),
      ),
    );
  }
}
