abstract interface class SensorDataSource {
  Stream<String> get messages;

  Future<void> start();

  Future<void> stop();

  Future<void> dispose();
}
