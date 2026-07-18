import 'daily_summary.dart';
import 'flower_parameters.dart';
import 'sensor_data.dart';
import 'validation_result.dart';

class BackendSnapshot {
  const BackendSnapshot({
    required this.emittedAt,
    this.latestData,
    this.validation,
    this.dailySummary,
    this.flowerParameters,
    this.errorMessage,
  });

  final DateTime emittedAt;
  final SensorData? latestData;
  final ValidationResult? validation;
  final DailySummary? dailySummary;
  final FlowerParameters? flowerParameters;
  final String? errorMessage;

  bool get hasError => errorMessage != null;
}
