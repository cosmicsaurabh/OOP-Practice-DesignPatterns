# OOP Practice - Design Patterns in C++

A comprehensive collection of Object-Oriented Programming implementations and Design Pattern examples in C++. This repository demonstrates various software design patterns, data structures, and best practices in modern C++ development.

## 📚 Table of Contents

- [Overview](#overview)
- [Implemented Patterns & Systems](#implemented-patterns--systems)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Implementation Details](#implementation-details)
- [Key Features](#key-features)
- [Contributing](#contributing)
- [License](#license)

## 🎯 Overview

This repository contains practical implementations of fundamental design patterns and data structures using C++. Each implementation follows industry best practices and includes comprehensive documentation, error handling, and real-world applicable examples.

## 🏗️ Implemented Patterns & Systems

### 1. **Strategy Pattern** - Social Media User Management System

- **File**: `c++/StrategyPattern_PaymentGateway.cpp`
- **Design Pattern**: Strategy Pattern + Role-based Access Control
- **Features**:
  - Role-based user hierarchy (Admin, Moderator, User)
  - CRUD operations with role validation
  - Protection against removing the last admin
  - Scalable architecture for large user bases

### 2. **Strategy + Factory Pattern** - Payment Gateway System

- **File**: `c++/Payment_Gateway.cpp`
- **Design Patterns**: Strategy Pattern + Factory Pattern
- **Features**:
  - Multiple payment processors (Visa, MasterCard)
  - Transaction management and status tracking
  - Random transaction ID generation
  - Comprehensive error handling and validation
  - Extensible architecture for new payment methods

### 3. **Data Structure** - Queue Implementation using Linked List

- **File**: `c++/Queue_using_LinkedLIst.cpp`
- **Implementation**: Custom Queue with Linked List
- **Features**:
  - FIFO (First In, First Out) operations
  - Dynamic memory management
  - Edge case handling for empty queue
  - Memory leak prevention with proper destructor

## 📁 Project Structure

```
OOP-practice-designpattern/
├── c++/
│   ├── StrategyPattern_PaymentGateway.cpp    # User Management System
│   ├── Payment_Gateway.cpp                   # Payment Gateway System
│   └── Queue_using_LinkedLIst.cpp           # Queue Data Structure
├── README.md                                 # Project documentation
└── .gitignore                               # Git ignore rules
```

## 🚀 Getting Started

### Prerequisites

- C++ compiler (GCC 7+ or Clang 6+ recommended)
- Standard C++11 or later
- Git for version control

### Installation & Running

1. **Clone the repository**:

   ```bash
   git clone https://github.com/cosmicsaurabh/OOP-Practice-DesignPatterns.git
   cd OOP-Practice-DesignPatterns
   ```

2. **Compile any implementation**:

   ```bash
   # For User Management System
   g++ -std=c++11 -o user_management c++/StrategyPattern_PaymentGateway.cpp
   ./user_management

   # For Payment Gateway System
   g++ -std=c++11 -o payment_gateway c++/Payment_Gateway.cpp
   ./payment_gateway

   # For Queue Implementation
   g++ -std=c++11 -o queue_demo c++/Queue_using_LinkedLIst.cpp
   ./queue_demo
   ```

3. **Alternative compilation with optimization**:
   ```bash
   g++ -std=c++17 -O2 -Wall -Wextra -o program_name source_file.cpp
   ```

## 💡 Implementation Details

### User Management System

```cpp
// Example usage
UserManager manager;
manager.addNewUser("Alice", ADMIN_ROLE);
manager.addNewUser("Bob", MOD_ROLE);
manager.changeRole("Bob", ADMIN_ROLE);
manager.viewAllUsers();
```

### Payment Gateway System

```cpp
// Example usage
PaymentManager manager;
string key = manager.startPaymentProcess(Gateway::VISA, 500.75);
manager.getPaymentStatus(key);
manager.listAllPayments();
```

### Queue Data Structure

```cpp
// Example usage
Queue q;
q.push(10);
q.push(20);
cout << "Front: " << q.front();  // Output: 10
cout << "Size: " << q.size();    // Output: 2
q.pop();
```

## ✨ Key Features

### 🏛️ **Design Patterns Demonstrated**

- **Strategy Pattern**: Interchangeable algorithms and behaviors
- **Factory Pattern**: Object creation without specifying exact classes
- **Polymorphism**: Runtime method resolution through virtual functions

### 🛡️ **Best Practices Implemented**

- **RAII** (Resource Acquisition Is Initialization)
- **Smart Pointers** for automatic memory management
- **Const Correctness** throughout the codebase
- **Exception Safety** with proper error handling
- **Single Responsibility Principle**
- **Open/Closed Principle** for extensibility

### 🔧 **Modern C++ Features**

- Scoped enumerations (`enum class`)
- Auto type deduction
- Range-based for loops
- Smart pointers (`shared_ptr`, `unique_ptr`)
- Move semantics where applicable

### 📋 **Code Quality**

- Comprehensive documentation with Doxygen-style comments
- Consistent naming conventions
- Input validation and error handling
- Memory leak prevention
- Clean, readable code structure

## 🧪 Testing

Each implementation includes a `main()` function with comprehensive test scenarios:

- **Positive test cases**: Normal operation flows
- **Negative test cases**: Error conditions and edge cases
- **Boundary testing**: Empty containers, invalid inputs
- **Integration testing**: Multiple operations in sequence

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. **Fork the repository**
2. **Create a feature branch**: `git checkout -b feature/new-pattern`
3. **Commit your changes**: `git commit -m "Add Observer Pattern implementation"`
4. **Push to the branch**: `git push origin feature/new-pattern`
5. **Submit a Pull Request**

### Contribution Guidelines

- Follow existing code style and naming conventions
- Add comprehensive documentation for new implementations
- Include test cases in the main function
- Update README.md with new pattern descriptions

## 📝 Future Implementations

Planned additions to this repository:

- [ ] Observer Pattern (Publisher-Subscriber)
- [ ] Singleton Pattern (Thread-safe implementation)
- [ ] Builder Pattern (Complex object construction)
- [ ] Decorator Pattern (Dynamic behavior extension)
- [ ] Command Pattern (Encapsulating requests)
- [ ] Adapter Pattern (Interface compatibility)
- [ ] State Pattern (State-dependent behavior)

## 📖 Learning Resources

## 👨‍💻 Author

**Saurabh** - [cosmicsaurabh](https://github.com/cosmicsaurabh)

## 🌟 Acknowledgments

- Inspiration from Gang of Four Design Patterns
- Modern C++ community best practices
- Real-world software development scenarios

---

⭐ **Star this repository** if you find it helpful for learning OOP and Design Patterns!

💬 **Questions or suggestions?** Feel free to open an issue or reach out!
