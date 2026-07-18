import 'dart:convert';

import '../models/sensor_data.dart';

class DataParser {
  const DataParser();

  SensorData parse(String rawMessage) {
    final dynamic decoded;

    try {
      decoded = jsonDecode(rawMessage.trim());
    } on FormatException catch (error) {
      throw FormatException('Invalid JSON: ${error.message}');
    }

    if (decoded is! Map<String, dynamic>) {
      throw const FormatException('The JSON root must be an object.');
    }

    return SensorData(
      schemaVersion: _readOptionalInt(decoded, 'schema_version') ?? 1,
      timestamp: _readDateTime(decoded, 'timestamp'),
      heartbeat: _readInt(decoded, 'heartbeat'),
      spo2: _readInt(decoded, 'spo2'),
      skinTemp: _readDouble(decoded, 'skin_temp'),
      activity: _readInt(decoded, 'activity'),
    );
  }

  int _readInt(Map<String, dynamic> json, String key) {
    final value = _required(json, key);
    if (value is int) return value;
    if (value is num && value.isFinite && value == value.roundToDouble()) {
      return value.toInt();
    }
    throw FormatException('Field "$key" must be an integer.');
  }

  int? _readOptionalInt(Map<String, dynamic> json, String key) {
    if (!json.containsKey(key) || json[key] == null) return null;
    return _readInt(json, key);
  }

  double _readDouble(Map<String, dynamic> json, String key) {
    final value = _required(json, key);
    if (value is num && value.isFinite) return value.toDouble();
    throw FormatException('Field "$key" must be a number.');
  }

  DateTime _readDateTime(Map<String, dynamic> json, String key) {
    final value = _required(json, key);
    if (value is! String) {
      throw FormatException('Field "$key" must be an ISO 8601 string.');
    }

    final parsed = DateTime.tryParse(value);
    if (parsed == null) {
      throw FormatException('Field "$key" is not a valid ISO 8601 time.');
    }
    return parsed;
  }

  dynamic _required(Map<String, dynamic> json, String key) {
    if (!json.containsKey(key) || json[key] == null) {
      throw FormatException('Missing required field "$key".');
    }
    return json[key];
  }
}
