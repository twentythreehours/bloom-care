import 'dart:async';
import 'dart:convert';
import 'dart:math';

import 'sensor_data_source.dart';

class MockSensorDataSource implements SensorDataSource {
  MockSensorDataSource({
    this.interval = const Duration(seconds: 2),
    Random? random,
  }) : _random = random ?? Random();

  final Duration interval;
  final Random _random;
  final StreamController<String> _controller =
      StreamController<String>.broadcast();

  Timer? _timer;

  @override
  Stream<String> get messages => _controller.stream;

  @override
  Future<void> start() async {
    if (_timer != null) return;
    _emitSample();
    _timer = Timer.periodic(interval, (_) => _emitSample());
  }

  void _emitSample() {
    final json = <String, dynamic>{
      'schema_version': 1,
      'timestamp': DateTime.now().toUtc().toIso8601String(),
      'heartbeat': 68 + _random.nextInt(25),
      'spo2': 95 + _random.nextInt(5),
      'skin_temp': 36.2 + (_random.nextDouble() * 0.8),
      'activity': 20 + _random.nextInt(61),
    };
    _controller.add(jsonEncode(json));
  }

  @override
  Future<void> stop() async {
    _timer?.cancel();
    _timer = null;
  }

  @override
  Future<void> dispose() async {
    await stop();
    await _controller.close();
  }
}
