// Mirrors app/bloom_care/lib/app-backend-code/data_sources/mock_sensor_data_source.dart
// Same JSON schema (schema_version, timestamp, heartbeat, spo2, skin_temp, activity) so this
// slots in wherever the real BLE-backed source will later. Values drift with a bounded random
// walk instead of independent random draws per tick, since that reads as a live sensor rather
// than noise.

const HEARTBEAT_RANGE = [58, 100];
const SPO2_RANGE = [94, 99];
const SKIN_TEMP_RANGE = [36.1, 37.0];
const ACTIVITY_RANGE = [10, 90];

function clamp(value, min, max) {
  return Math.min(max, Math.max(min, value));
}

function randomInRange([min, max]) {
  return min + Math.random() * (max - min);
}

function step(previous, [min, max], maxDelta) {
  const delta = (Math.random() * 2 - 1) * maxDelta;
  return clamp(previous + delta, min, max);
}

export function createInitialSample() {
  return {
    schema_version: 1,
    timestamp: new Date().toISOString(),
    heartbeat: Math.round(randomInRange(HEARTBEAT_RANGE)),
    spo2: Math.round(randomInRange(SPO2_RANGE)),
    skin_temp: Number(randomInRange(SKIN_TEMP_RANGE).toFixed(2)),
    activity: Math.round(randomInRange(ACTIVITY_RANGE)),
  };
}

export function nextSample(previous) {
  return {
    schema_version: 1,
    timestamp: new Date().toISOString(),
    heartbeat: Math.round(step(previous.heartbeat, HEARTBEAT_RANGE, 3)),
    spo2: Math.round(step(previous.spo2, SPO2_RANGE, 1)),
    skin_temp: Number(step(previous.skin_temp, SKIN_TEMP_RANGE, 0.08).toFixed(2)),
    activity: Math.round(step(previous.activity, ACTIVITY_RANGE, 6)),
  };
}
