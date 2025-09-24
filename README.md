# DSA Course Template 🚀

[![DSA Assignment Auto-Grader](https://github.com/username/dsa-course-template/actions/workflows/test-assignments.yml/badge.svg)](https://github.com/username/dsa-course-template/actions/workflows/test-assignments.yml)

**A comprehensive GitHub repository template for Data Structures and Algorithms course using C++.**

This template provides a complete, production-ready course structure for teaching DSA. It includes automated testing, development environment setup, and 7 weeks of comprehensive assignments covering all major DSA topics from arrays to graph algorithms.

## 🚀 Getting Started

### Prerequisites
- GitHub account
- Visual Studio Code
- Docker (for dev container)

### Setup Instructions

1. **Use this template**: Click the "Use this template" button on GitHub to create your own repository
2. **Clone your repository**: 
   ```bash
   git clone https://github.com/yourusername/your-repo-name.git
   cd your-repo-name
   ```
3. **Open in VS Code**: 
   ```bash
   code .
   ```
4. **Reopen in Container**: When prompted, click "Reopen in Container" or use Ctrl+Shift+P → "Dev Containers: Reopen in Container"

## 📁 Repository Structure

```
├── .devcontainer/          # Development container configuration
├── .github/
│   ├── workflows/          # GitHub Actions for automated testing
│   └── copilot-instructions.md
├── assignment-descriptions/ # Official PDF assignment descriptions
├── assignments/            # Weekly assignments
│   ├── week01-arrays/
│   ├── week02-linked-lists/
│   └── week03-stacks-queues/
├── tests/                  # Automated test suites
├── resources/              # Course materials and references
└── README.md
```

## 📚 Assignments

Each week's assignment is contained in its own directory under `assignments/`. The official assignment descriptions are provided as PDF files in the `assignment-descriptions/` folder. Each assignment includes:

- **PDF Description**: Official requirements in `assignment-descriptions/weekXX-topic.pdf`
- **README.md**: Assignment summary and requirements
- **Template files**: C++ files with function signatures and documentation
- **Test cases**: Automated tests to verify your implementation

### Current Assignments

- **Week 1**: Arrays and Basic Operations
- **Week 2**: Linked Lists
- **Week 3**: Stacks and Queues

## 🧪 Testing Your Code

### Local Testing
The dev container includes all necessary tools for compiling and testing:

```bash
# Navigate to assignment directory
cd assignments/week01-arrays

# Compile your code
g++ -std=c++17 -Wall -Wextra -o array_ops array_operations.cpp

# Run basic tests (manual)
./array_ops
```

### Automated Testing
Every time you push code to GitHub, automated tests will run:

1. **Compilation check**: Ensures your code compiles without errors
2. **Functionality tests**: Runs comprehensive test suites
3. **Memory leak detection**: Uses Valgrind to check for memory issues
4. **Code style check**: Verifies adherence to coding standards

View test results in the "Actions" tab of your GitHub repository.

## 💻 Development Environment

This template includes a preconfigured development container with:

- **C++ Compiler**: GCC and Clang
- **Build Tools**: CMake, Make
- **Debugging Tools**: GDB, Valgrind
- **VS Code Extensions**: 
  - C/C++ Extension Pack
  - CMake Tools
  - GitHub Copilot
  - Test Explorer

## 📝 Assignment Submission

1. **Complete the assignment** in the appropriate directory
2. **Test locally** to ensure your code works
3. **Commit and push** your changes:
   ```bash
   git add .
   git commit -m "Complete Week 1 array operations"
   git push origin main
   ```
4. **Check GitHub Actions** for automated test results
5. **Fix any issues** identified by the tests

## 🎯 Coding Standards

- Use **C++17** standard
- Follow consistent naming conventions
- Include proper error handling
- Add time/space complexity comments
- Write clean, readable code
- Handle edge cases appropriately

## 🔧 Troubleshooting

### Dev Container Issues
If the dev container fails to start:
1. Ensure Docker is running
2. Rebuild the container: Ctrl+Shift+P → "Dev Containers: Rebuild Container"

### Compilation Errors
- Check that you're using C++17 standard
- Ensure all required headers are included
- Verify function signatures match the requirements

### Test Failures
- Read error messages carefully
- Check edge cases and boundary conditions
- Ensure your algorithm logic is correct
- Verify input validation

## 📖 Resources

- [Course Resources](./resources/README.md)
- [C++ Reference](https://cppreference.com/)
- [Algorithm Visualizations](https://visualgo.net/)
- [Big O Cheat Sheet](https://www.bigocheatsheet.com/)

## 🤝 Getting Help

1. **Read the assignment README** thoroughly
2. **Check the test cases** to understand expected behavior
3. **Use GitHub Discussions** for questions
4. **Office hours**: [Insert schedule]
5. **Email instructor**: [Insert email]

## 📋 Grading Criteria

Assignments are evaluated on:
- **Correctness** (60%): Does your code produce correct results?
- **Efficiency** (20%): Is your algorithm optimal?
- **Code Quality** (15%): Is your code clean and well-documented?
- **Testing** (5%): Do all tests pass?

## 🔄 Template Updates

This template may be updated throughout the semester. To get updates:

```bash
# Add the template repository as upstream
git remote add template https://github.com/instructor/dsa-course-template.git

# Fetch and merge updates
git fetch template
git merge template/main
```

## 📄 License

This educational template is provided under the MIT License. See [LICENSE](LICENSE) for details.

---

**Happy Coding! 🎉**

Remember: The goal is not just to pass tests, but to understand the underlying concepts and develop problem-solving skills that will serve you throughout your career in computer science.