import '../models/daily_summary.dart';
import '../models/sensor_data.dart';

class DailyDataService {
  const DailyDataService();

  DailySummary summarize(List<SensorData> samples, DateTime day) {
    if (samples.isEmpty) {
      throw StateError('Cannot summarize an empty day.');
    }

    double sum(num Function(SensorData item) select) => samples.fold<double>(
          0,
          (total, item) => total + select(item).toDouble(),
        );

    final count = samples.length;
    return DailySummary(
      date: DateTime(day.year, day.month, day.day),
      sampleCount: count,
      averageHeartbeat: sum((item) => item.heartbeat) / count,
      averageSpo2: sum((item) => item.spo2) / count,
      averageSkinTemp: sum((item) => item.skinTemp) / count,
      averageActivity: sum((item) => item.activity) / count,
    );
  }
}
