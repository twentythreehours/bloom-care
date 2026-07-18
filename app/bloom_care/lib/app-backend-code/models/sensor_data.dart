class SensorData {
  const SensorData({
    required this.timestamp,
    required this.heartbeat,
    required this.spo2,
    required this.skinTemp,
    required this.activity,
    this.schemaVersion = 1,
  });

  final int schemaVersion;
  final DateTime timestamp;
  final int heartbeat;
  final int spo2;
  final double skinTemp;
  final int activity;

  Map<String, dynamic> toJson() {
    return <String, dynamic>{
      'schema_version': schemaVersion,
      'timestamp': timestamp.toUtc().toIso8601String(),
      'heartbeat': heartbeat,
      'spo2': spo2,
      'skin_temp': skinTemp,
      'activity': activity,
    };
  }

  @override
  String toString() => 'SensorData(${toJson()})';
}
