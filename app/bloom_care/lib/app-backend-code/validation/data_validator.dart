import '../models/sensor_data.dart';
import '../models/validation_result.dart';

class DataValidator {
  const DataValidator();

  ValidationResult validate(SensorData data) {
    final issues = <ValidationIssue>[];

    if (data.schemaVersion != 1) {
      issues.add(const ValidationIssue(
        field: 'schema_version',
        message: 'Only schema version 1 is currently supported.',
        severity: ValidationSeverity.error,
      ));
    }

    if (data.heartbeat < 30 || data.heartbeat > 220) {
      issues.add(const ValidationIssue(
        field: 'heartbeat',
        message: 'Heartbeat is outside the accepted technical range 30-220.',
        severity: ValidationSeverity.error,
      ));
    } else if (data.heartbeat < 50 || data.heartbeat > 120) {
      issues.add(const ValidationIssue(
        field: 'heartbeat',
        message: 'Heartbeat is outside the prototype expected range 50-120.',
        severity: ValidationSeverity.warning,
      ));
    }

    if (data.spo2 < 0 || data.spo2 > 100) {
      issues.add(const ValidationIssue(
        field: 'spo2',
        message: 'SpO2 must be between 0 and 100.',
        severity: ValidationSeverity.error,
      ));
    } else if (data.spo2 < 90) {
      issues.add(const ValidationIssue(
        field: 'spo2',
        message: 'SpO2 is below the prototype expected range.',
        severity: ValidationSeverity.warning,
      ));
    }

    if (data.skinTemp < 20 || data.skinTemp > 45) {
      issues.add(const ValidationIssue(
        field: 'skin_temp',
        message: 'Skin temperature is outside the accepted technical range.',
        severity: ValidationSeverity.error,
      ));
    } else if (data.skinTemp < 36.3 || data.skinTemp > 36.8) {
      issues.add(const ValidationIssue(
        field: 'skin_temp',
        message: 'Skin temperature will produce a cool or warm hue shift.',
        severity: ValidationSeverity.warning,
      ));
    }

    if (data.activity < 0 || data.activity > 100) {
      issues.add(const ValidationIssue(
        field: 'activity',
        message: 'Activity must be between 0 and 100.',
        severity: ValidationSeverity.error,
      ));
    }

    final fiveMinutesFromNow = DateTime.now().toUtc().add(
          const Duration(minutes: 5),
        );
    if (data.timestamp.toUtc().isAfter(fiveMinutesFromNow)) {
      issues.add(const ValidationIssue(
        field: 'timestamp',
        message: 'Timestamp is unexpectedly far in the future.',
        severity: ValidationSeverity.warning,
      ));
    }

    return ValidationResult(List.unmodifiable(issues));
  }
}
