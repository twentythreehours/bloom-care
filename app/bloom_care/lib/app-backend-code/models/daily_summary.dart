class DailySummary {
  const DailySummary({
    required this.date,
    required this.sampleCount,
    required this.averageHeartbeat,
    required this.averageSpo2,
    required this.averageSkinTemp,
    required this.averageActivity,
  });

  final DateTime date;
  final int sampleCount;
  final double averageHeartbeat;
  final double averageSpo2;
  final double averageSkinTemp;
  final double averageActivity;

  Map<String, dynamic> toJson() {
    return <String, dynamic>{
      'date': _dateOnly(date),
      'sample_count': sampleCount,
      'average_heartbeat': averageHeartbeat,
      'average_spo2': averageSpo2,
      'average_skin_temp': averageSkinTemp,
      'average_activity': averageActivity,
    };
  }

  String _dateOnly(DateTime value) {
    final local = value.toLocal();
    final month = local.month.toString().padLeft(2, '0');
    final day = local.day.toString().padLeft(2, '0');
    return '${local.year}-$month-$day';
  }
}
