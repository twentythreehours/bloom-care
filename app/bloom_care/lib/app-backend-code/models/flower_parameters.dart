class FlowerParameters {
  const FlowerParameters({
    required this.hueShiftDegrees,
    required this.saturation,
    required this.petalOpenness,
    required this.pulseBpm,
    required this.growthHeight,
  });

  final double hueShiftDegrees;
  final double saturation;
  final double petalOpenness;
  final double pulseBpm;
  final double growthHeight;

  Map<String, dynamic> toJson() {
    return <String, dynamic>{
      'hue_shift_degrees': hueShiftDegrees,
      'saturation': saturation,
      'petal_openness': petalOpenness,
      'pulse_bpm': pulseBpm,
      'growth_height': growthHeight,
    };
  }
}
