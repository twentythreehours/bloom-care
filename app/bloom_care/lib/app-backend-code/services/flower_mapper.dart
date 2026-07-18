import '../models/daily_summary.dart';
import '../models/flower_parameters.dart';

class FlowerMapper {
  const FlowerMapper();

  FlowerParameters map(
    DailySummary summary, {
    double growthHeight = 0,
  }) {
    final hueShift = _normalize(
      summary.averageSkinTemp,
      inputMin: 36.3,
      inputMax: 36.8,
      outputMin: -20,
      outputMax: 20,
    );

    final saturation = _normalize(
      summary.averageSpo2,
      inputMin: 90,
      inputMax: 100,
      outputMin: 0.55,
      outputMax: 1,
    );

    // In this prototype, activity means movement during sleep.
    // More movement therefore produces a less open flower.
    final petalOpenness =
        (1 - (summary.averageActivity / 100).clamp(0, 1)).toDouble();

    return FlowerParameters(
      hueShiftDegrees: hueShift,
      saturation: saturation,
      petalOpenness: petalOpenness,
      pulseBpm: summary.averageHeartbeat,
      growthHeight: growthHeight.clamp(0, 1).toDouble(),
    );
  }

  double _normalize(
    double value, {
    required double inputMin,
    required double inputMax,
    required double outputMin,
    required double outputMax,
  }) {
    final ratio =
        ((value - inputMin) / (inputMax - inputMin)).clamp(0, 1).toDouble();
    return outputMin + ratio * (outputMax - outputMin);
  }
}
