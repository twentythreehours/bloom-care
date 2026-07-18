import 'dart:async';

import '../data_sources/sensor_data_source.dart';
import '../models/backend_snapshot.dart';
import '../parsing/data_parser.dart';
import '../repositories/sensor_data_repository.dart';
import '../validation/data_validator.dart';
import 'daily_data_service.dart';
import 'flower_mapper.dart';

class BloomCareBackend {
  BloomCareBackend({
    required SensorDataSource dataSource,
    required SensorDataRepository repository,
    DataParser parser = const DataParser(),
    DataValidator validator = const DataValidator(),
    DailyDataService dailyDataService = const DailyDataService(),
    FlowerMapper flowerMapper = const FlowerMapper(),
  })  : _dataSource = dataSource,
        _repository = repository,
        _parser = parser,
        _validator = validator,
        _dailyDataService = dailyDataService,
        _flowerMapper = flowerMapper;

  final SensorDataSource _dataSource;
  final SensorDataRepository _repository;
  final DataParser _parser;
  final DataValidator _validator;
  final DailyDataService _dailyDataService;
  final FlowerMapper _flowerMapper;

  final StreamController<BackendSnapshot> _snapshots =
      StreamController<BackendSnapshot>.broadcast();

  StreamSubscription<String>? _messageSubscription;

  Stream<BackendSnapshot> get snapshots => _snapshots.stream;

  Future<void> start() async {
    if (_messageSubscription != null) return;

    _messageSubscription = _dataSource.messages.listen(
      (message) => _process(message),
      onError: (Object error, StackTrace stackTrace) {
        _emitError('Data source error: $error');
      },
    );

    await _dataSource.start();
  }

  Future<void> _process(String rawMessage) async {
    try {
      final data = _parser.parse(rawMessage);
      final validation = _validator.validate(data);

      if (!validation.isValid) {
        _snapshots.add(BackendSnapshot(
          emittedAt: DateTime.now(),
          latestData: data,
          validation: validation,
          errorMessage: 'Sensor data failed validation.',
        ));
        return;
      }

      await _repository.save(data);
      final localDay = data.timestamp.toLocal();
      final samples = await _repository.findByDay(localDay);
      final summary = _dailyDataService.summarize(samples, localDay);
      final flower = _flowerMapper.map(summary);

      _snapshots.add(BackendSnapshot(
        emittedAt: DateTime.now(),
        latestData: data,
        validation: validation,
        dailySummary: summary,
        flowerParameters: flower,
      ));
    } on FormatException catch (error) {
      _emitError(error.message.toString());
    } catch (error) {
      _emitError('Unexpected backend error: $error');
    }
  }

  void _emitError(String message) {
    if (_snapshots.isClosed) return;
    _snapshots.add(BackendSnapshot(
      emittedAt: DateTime.now(),
      errorMessage: message,
    ));
  }

  Future<void> stop() async {
    await _dataSource.stop();
    await _messageSubscription?.cancel();
    _messageSubscription = null;
  }

  Future<void> dispose() async {
    await stop();
    await _dataSource.dispose();
    await _snapshots.close();
  }
}
