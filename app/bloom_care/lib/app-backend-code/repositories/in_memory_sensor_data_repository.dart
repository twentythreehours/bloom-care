import '../models/sensor_data.dart';
import 'sensor_data_repository.dart';

class InMemorySensorDataRepository implements SensorDataRepository {
  final List<SensorData> _items = <SensorData>[];

  @override
  Future<void> save(SensorData data) async {
    _items.add(data);
    _items.sort((a, b) => a.timestamp.compareTo(b.timestamp));
  }

  @override
  Future<List<SensorData>> findByDay(DateTime day) async {
    final target = day.toLocal();
    return List.unmodifiable(_items.where((item) {
      final local = item.timestamp.toLocal();
      return local.year == target.year &&
          local.month == target.month &&
          local.day == target.day;
    }));
  }

  @override
  Future<void> clear() async {
    _items.clear();
  }
}
