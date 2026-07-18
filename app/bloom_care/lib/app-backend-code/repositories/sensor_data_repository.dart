import '../models/sensor_data.dart';

abstract interface class SensorDataRepository {
  Future<void> save(SensorData data);

  Future<List<SensorData>> findByDay(DateTime day);

  Future<void> clear();
}
