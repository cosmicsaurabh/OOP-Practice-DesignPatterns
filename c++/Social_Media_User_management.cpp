/*
 * Social Media User Management System
 * 
 * A social media company, SocialNet, wants to design a system to handle different types of users. 
 * The system should be able to handle users with varying levels of access and privileges. 
 * The company wants to design a class structure that can efficiently handle the different types of users. 
 * The system should be able to add new users, remove existing users, and display information about all users.
 *
 * The system should have the following types of users:
 * - Admin: Admin has access to all features of the system.
 * - Moderator: Moderator has access to moderate posts but cannot access admin features.
 * - User: User can post and view posts but cannot access moderator or admin features.
 *
 * Design the class structure for the above system using C++. You should define the classes, 
 * attributes, and methods required to implement the system.
 *
 * Note: You can use abstract classes, interfaces, or any other OOP concepts as per your requirement.
 * Assumptions: You can assume that the system will always have at least one Admin user.
 * Constraints:
 * - You cannot use any built-in Java classes for handling user access control.
 * - You should design the class structure in such a way that it is scalable and can handle a large number of users.
 */

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

using namespace std;

// Enumeration for user roles
enum Role { 
    ADMIN_ROLE, 
    MOD_ROLE, 
    USER_ROLE 
};

/**
 * Abstract base class for all users
 * Defines the common interface for all user types
 */
class BaseUser {
public:
    string name;
    
    explicit BaseUser(const string& name) : name(name) {}
    
    virtual string getRoleName() = 0;
    virtual void printInfo() = 0;
    virtual ~BaseUser() = default;
};

/**
 * Admin class - has access to all features
 * Inherits from BaseUser and implements admin-specific functionality
 */
class Admin : public BaseUser {
public:
    explicit Admin(const string& name) : BaseUser(name) {}
    
    string getRoleName() override {
        return "ADMIN";
    }
    
    void printInfo() override {
        cout << "Name: " << name << " || Role: ADMIN" << endl;
    }
};

/**
 * Moderator class - can moderate posts
 * Inherits from BaseUser and implements moderator-specific functionality
 */
class Moderator : public BaseUser {
public:
    explicit Moderator(const string& name) : BaseUser(name) {}
    
    string getRoleName() override {
        return "MOD";
    }
    
    void printInfo() override {
        cout << "Name: " << name << " || Role: MOD" << endl;
    }
};

/**
 * User class - basic user with limited privileges
 * Inherits from BaseUser and implements basic user functionality
 */
class User : public BaseUser {
public:
    explicit User(const string& name) : BaseUser(name) {}
    
    string getRoleName() override {
        return "USER";
    }
    
    void printInfo() override {
        cout << "Name: " << name << " || Role: USER" << endl;
    }
};

/**
 * UserManager class - manages all users in the system
 * Provides functionality to add, remove, and modify users
 */
class UserManager {
private:
    unordered_map<string, shared_ptr<BaseUser>> users;
    int adminCount = 0;
    int modCount = 0;
    int userCount = 0;

public:
    /**
     * Adds a new user to the system
     * @param name The name of the user
     * @param role The role of the user
     * @return true if user was added successfully, false otherwise
     */
    bool addNewUser(const string& name, Role role) {
        if (users.find(name) != users.end()) {
            cout << "User already exists." << endl;
            return false;
        }
        
        shared_ptr<BaseUser> newUser;
        
        switch (role) {
            case ADMIN_ROLE:
                adminCount++;
                newUser = make_shared<Admin>(name);
                break;
            case MOD_ROLE:
                modCount++;
                newUser = make_shared<Moderator>(name);
                break;
            case USER_ROLE:
                userCount++;
                newUser = make_shared<User>(name);
                break;
        }
        
        users[name] = newUser;
        cout << "User '" << name << "' added successfully." << endl;
        return true;
    }

    /**
     * Removes a user from the system
     * @param name The name of the user to remove
     * @return true if user was removed successfully, false otherwise
     */
    bool removeUser(const string& name) {
        if (users.find(name) == users.end()) {
            cout << "User does not exist." << endl;
            return false;
        }

        string role = users[name]->getRoleName();
        
        // Prevent removal of the last admin
        if (role == "ADMIN" && adminCount <= 1) {
            cout << "Cannot remove the last admin user." << endl;
            return false;
        }

        // Update counters
        if (role == "ADMIN") {
            adminCount--;
        } else if (role == "MOD") {
            modCount--;
        } else {
            userCount--;
        }

        users.erase(name);
        cout << "User '" << name << "' removed successfully." << endl;
        return true;
    }
    
    /**
     * Changes the role of an existing user
     * @param name The name of the user
     * @param newRole The new role to assign
     * @return true if role was changed successfully, false otherwise
     */
    bool changeRole(const string& name, Role newRole) {
        if (users.find(name) == users.end()) {
            cout << "User does not exist." << endl;
            return false;
        }
        
        string currentRole = users[name]->getRoleName();
        
        // Check if user already has the same role
        if ((newRole == ADMIN_ROLE && currentRole == "ADMIN") ||
            (newRole == MOD_ROLE && currentRole == "MOD") ||
            (newRole == USER_ROLE && currentRole == "USER")) {
            cout << "User already has the same role." << endl;
            return false;
        }
        
        // Update counters for old role
        if (currentRole == "ADMIN") {
            adminCount--;
        } else if (currentRole == "MOD") {
            modCount--;
        } else {
            userCount--;
        }
        
        // Create new user object with new role
        switch (newRole) {
            case ADMIN_ROLE:
                adminCount++;
                users[name] = make_shared<Admin>(name);
                break;
            case MOD_ROLE:
                modCount++;
                users[name] = make_shared<Moderator>(name);
                break;
            case USER_ROLE:
                userCount++;
                users[name] = make_shared<User>(name);
                break;
        }
        
        cout << "Role changed successfully for user '" << name << "'." << endl;
        return true;
    }

    /**
     * Displays information about all users in the system
     */
    void viewAllUsers() {
        if (users.empty()) {
            cout << "No users in the system." << endl;
            return;
        }
        
        cout << "\n=== All Users ===" << endl;
        for (const auto& user : users) {
            user.second->printInfo();
        }
        cout << "\nTotal Users: " << users.size() 
             << " (Admins: " << adminCount 
             << ", Moderators: " << modCount 
             << ", Users: " << userCount << ")" << endl;
    }
};

/**
 * Main function - demonstrates the user management system
 */
int main() {
    UserManager manager;

    cout << "=== Social Media User Management System ===" << endl;
    
    // Add initial users
    cout << "\n--- Adding Users ---" << endl;
    manager.addNewUser("Alice", ADMIN_ROLE);
    manager.addNewUser("Bob", MOD_ROLE);
    manager.addNewUser("Charlie", USER_ROLE);

    // Display all users
    manager.viewAllUsers();

    // Test user removal
    cout << "\n--- Testing User Removal ---" << endl;
    manager.removeUser("Alice");  // Should block removal (last admin)
    manager.removeUser("Charlie"); // Should succeed

    // Display users after removal
    manager.viewAllUsers();
    
    // Test role change
    cout << "\n--- Testing Role Change ---" << endl;
    manager.changeRole("Bob", ADMIN_ROLE);

    // Display final state
    manager.viewAllUsers();

    return 0;
}