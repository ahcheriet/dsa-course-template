# Contributing to DSA Course Template

Thank you for your interest in improving this course template! This document provides guidelines for contributing to the project.

## How to Contribute

### For Instructors

#### Adding New Assignments
1. Create a new directory under `assignments/` following the naming convention `weekXX-topic`
2. Include:
   - `README.md` with assignment description and requirements
   - Template `.cpp` files with function signatures and documentation
   - Clear learning objectives and grading criteria

#### Adding Test Cases
1. Create corresponding test directory under `tests/`
2. Write comprehensive test cases using Google Test framework
3. Include edge cases and boundary conditions
4. Test both correct implementations and error handling

#### Updating Workflows
1. Modify `.github/workflows/test-assignments.yml` to include new assignments
2. Ensure all assignments are properly tested
3. Update compilation and testing steps as needed

### For Students

#### Reporting Issues
1. Use the GitHub Issues tab to report problems
2. Include:
   - Clear description of the issue
   - Steps to reproduce
   - Expected vs actual behavior
   - Your development environment details

#### Suggesting Improvements
1. Open an issue with the "enhancement" label
2. Describe the improvement and its benefits
3. Provide examples if applicable

## Development Guidelines

### Code Style
- Follow the project's `.clang-format` configuration
- Use meaningful variable and function names
- Include proper documentation and comments
- Handle edge cases appropriately

### Testing
- All new code must include appropriate tests
- Tests should cover normal cases, edge cases, and error conditions
- Ensure tests pass before submitting

### Documentation
- Update README files when adding new features
- Include clear examples and usage instructions
- Document any new dependencies or setup requirements

## Pull Request Process

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/new-assignment`)
3. Make your changes
4. Add/update tests as necessary
5. Ensure all tests pass
6. Update documentation
7. Submit a pull request with:
   - Clear description of changes
   - Reference to related issues
   - Screenshots/examples if applicable

## Review Process

- All contributions will be reviewed by course instructors
- Changes may be requested before acceptance
- Focus on educational value and clarity
- Ensure changes align with course objectives

## Questions?

If you have questions about contributing:
- Open an issue for discussion
- Contact the course instructor
- Check existing documentation and issues

Thank you for helping make this course better for everyone!