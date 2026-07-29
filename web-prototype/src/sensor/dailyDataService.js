// Mirrors app/bloom_care/lib/app-backend-code/services/daily_data_service.dart

export function summarize(samples) {
  const count = samples.length;
  if (count === 0) return null;

  const sum = (select) => samples.reduce((total, item) => total + select(item), 0);

  return {
    sampleCount: count,
    averageHeartbeat: sum((s) => s.heartbeat) / count,
    averageSpo2: sum((s) => s.spo2) / count,
    averageSkinTemp: sum((s) => s.skin_temp) / count,
    averageActivity: sum((s) => s.activity) / count,
  };
}
