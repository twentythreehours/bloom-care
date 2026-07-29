// Mirrors app/bloom_care/lib/app-backend-code/services/flower_mapper.dart
// Same normalization ranges, so the numbers here should match what the Flutter
// backend produces for the same sensor inputs once it's wired to real hardware.

function normalize(value, inputMin, inputMax, outputMin, outputMax) {
  const ratio = Math.min(1, Math.max(0, (value - inputMin) / (inputMax - inputMin)));
  return outputMin + ratio * (outputMax - outputMin);
}

export function mapToFlowerParameters(summary, growthHeight = 0) {
  const hueShiftDegrees = normalize(summary.averageSkinTemp, 36.3, 36.8, -20, 20);
  const saturation = normalize(summary.averageSpo2, 90, 100, 0.55, 1);

  // Same as the Dart version's comment: activity here means movement, so more
  // movement produces a less "open" flower.
  const petalOpenness = 1 - Math.min(1, Math.max(0, summary.averageActivity / 100));

  return {
    hueShiftDegrees,
    saturation,
    petalOpenness,
    pulseBpm: summary.averageHeartbeat,
    growthHeight: Math.min(1, Math.max(0, growthHeight)),
  };
}
