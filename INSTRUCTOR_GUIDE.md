# Instructor Guide: DSA Course Template

## Overview
This template provides a complete course structure for teaching Data Structures and Algorithms using C++. It includes 7 weeks of progressive assignments, automated testing, and a professional development environment.

## Course Structure

### Weekly Breakdown
- **Week 1**: Arrays and Basic Operations (Beginner)
- **Week 2**: Linked Lists - Singly and Doubly (Beginner-Intermediate)
- **Week 3**: Stacks, Queues, and Applications (Intermediate)
- **Week 4**: Binary Trees - BST and AVL (Intermediate-Advanced)
- **Week 5**: Hash Tables and Collision Resolution (Advanced)
- **Week 6**: Sorting Algorithms Analysis (Advanced)
- **Week 7**: Graph Algorithms (Advanced)

### Learning Progression
Each week builds upon previous concepts:
1. **Foundations**: Basic data manipulation and memory concepts
2. **Linear Structures**: Understanding pointers and dynamic memory
3. **Abstract Data Types**: Stack/queue operations and applications
4. **Tree Structures**: Hierarchical data and balancing algorithms
5. **Hash Tables**: Advanced data organization and collision handling
6. **Algorithms**: Complexity analysis and optimization techniques
7. **Graph Theory**: Advanced algorithms and real-world applications

## Setting Up Your Course

### 1. Repository Creation
1. Click "Use this template" on the GitHub repository
2. Name your repository (e.g., `cs-dsa-fall-2024`)
3. Set as public or private based on your preference
4. Clone to your local machine for customization

### 2. Customization
- **Assignment deadlines**: Update README files with your schedule
- **Grading criteria**: Modify rubrics in each week's README
- **Additional requirements**: Add specific course policies
- **Test cases**: Add institution-specific test cases if needed

### 3. Student Onboarding
Share these instructions with students:
```markdown
1. Fork the course repository
2. Clone your fork locally
3. Install VS Code and Docker Desktop
4. Open repository in VS Code
5. Accept "Reopen in Container" prompt
6. Start with Week 1 assignment
```

## Monitoring Student Progress

### GitHub Insights
- **Contributors**: Track student activity
- **Commit History**: Monitor progress over time
- **Pull Requests**: Review student submissions
- **Actions**: Check automated test results

### Assessment Strategies

#### Automated Assessment (70%)
- **Correctness**: Test case pass rate
- **Memory Safety**: Valgrind leak detection
- **Code Quality**: Compilation warnings
- **Performance**: Algorithm efficiency tests

#### Manual Assessment (30%)
- **Code Style**: Readability and organization
- **Documentation**: Comments and explanations
- **Design Decisions**: Algorithm choice justification
- **Edge Case Handling**: Robustness testing

## Grading Workflow

### Automated Grading
1. Students push code to their repository
2. GitHub Actions automatically runs tests
3. Results appear in Actions tab
4. Instructors can download test reports

### Manual Review Process
1. Navigate to student's repository
2. Review latest commits on main branch
3. Check GitHub Actions results
4. Examine code quality in browser
5. Leave feedback via issues or comments

## Common Student Issues

### Environment Setup
**Problem**: Dev container fails to build
**Solution**: 
- Ensure Docker Desktop is running
- Check system requirements
- Try rebuilding container

**Problem**: Tests fail locally but pass on GitHub
**Solution**:
- Check for platform-specific code
- Verify all dependencies are in container
- Ensure consistent compiler flags

### Assignment Difficulties
**Week 1**: Array bounds and memory management
**Week 2**: Pointer manipulation and memory leaks
**Week 3**: Stack overflow and queue underflow
**Week 4**: Tree balancing and recursion depth
**Week 5**: Hash function design and collision handling
**Week 6**: Algorithm complexity understanding
**Week 7**: Graph representation and traversal

## Advanced Features

### Custom Test Cases
Add institution-specific tests:
```cpp
// In tests/week01/custom_tests.cpp
TEST(CustomArrayTest, InstitutionSpecificRequirement) {
    // Your custom test logic
}
```

### Performance Benchmarking
Enable performance monitoring:
```cpp
// Time complexity verification
auto start = std::chrono::high_resolution_clock::now();
// Student's algorithm
auto end = std::chrono::high_resolution_clock::now();
// Verify within expected bounds
```

### Plagiarism Detection
- Monitor commit patterns for unusual activity
- Compare similar code structures across repositories
- Use GitHub's similarity detection features

## Troubleshooting

### Build Failures
1. Check CMakeLists.txt for missing files
2. Verify all source files compile individually
3. Ensure Google Test is properly linked
4. Review compiler error messages

### Test Failures
1. Verify test expectations match assignment requirements
2. Check for platform-specific behavior
3. Ensure test data is valid
4. Review memory management in student code

### Container Issues
1. Rebuild dev container from scratch
2. Update Docker Desktop to latest version
3. Check system disk space availability
4. Verify VS Code extensions are installed

## Best Practices

### For Instructors
- **Regular Updates**: Keep assignment descriptions current
- **Clear Expectations**: Provide detailed rubrics
- **Timely Feedback**: Review submissions promptly
- **Office Hours**: Be available for technical support

### Course Management
- **Version Control**: Tag stable versions of assignments
- **Backup Strategy**: Maintain copies of all repositories
- **Student Communication**: Use Issues for Q&A
- **Progress Tracking**: Monitor class-wide performance trends

## Support Resources

### Technical Support
- **GitHub Docs**: Repository management guidance
- **VS Code**: Dev container documentation
- **Docker**: Container troubleshooting guides

### Pedagogical Resources
- **Assignment Rubrics**: Provided in each week's folder
- **Common Mistakes**: Documentation in resources/
- **Extension Activities**: Advanced challenges for gifted students

## Conclusion

This template provides a solid foundation for modern CS education. The combination of automated testing, professional development tools, and comprehensive assignments creates an engaging learning environment that prepares students for industry expectations.

For questions or support, please open an issue in the template repository or contact the maintainers.