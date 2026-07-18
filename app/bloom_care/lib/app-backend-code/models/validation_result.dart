enum ValidationSeverity { warning, error }

class ValidationIssue {
  const ValidationIssue({
    required this.field,
    required this.message,
    required this.severity,
  });

  final String field;
  final String message;
  final ValidationSeverity severity;
}

class ValidationResult {
  const ValidationResult(this.issues);

  final List<ValidationIssue> issues;

  bool get isValid =>
      !issues.any((issue) => issue.severity == ValidationSeverity.error);

  List<ValidationIssue> get warnings => issues
      .where((issue) => issue.severity == ValidationSeverity.warning)
      .toList(growable: false);

  List<ValidationIssue> get errors => issues
      .where((issue) => issue.severity == ValidationSeverity.error)
      .toList(growable: false);
}
