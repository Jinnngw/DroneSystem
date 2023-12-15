# Drone Simulation Project - Group 16

### **Team Members and x500:**
- Benjamin Lee [lee02819]
- Jing Wang [wan01205]
- Lingyi Xu [xu001032]
- Adam Shahin [shahi068]

### **Project Overview:**
Our project is an advanced drone simulation system designed to realistically model drone delivery dynamics within an interactive environment. The simulation includes various entities like drones, humans, and car pirates, each exhibiting unique behaviors and interactions. The goal is to simulate real-world scenarios in drone delivery, focusing on the challenges and strategies involved in modern delivery systems.

### **How to Run the Simulation:**
- Clone the repository using: `git clone git@github.umn.edu:umn-csci-3081-f23/team-001-16-hw4.git`.
- Navigate to the project directory.
- Execute `make clean; make run`.
- The simulation interface will launch, displaying the interactive environment.

### **Simulation Features:**
- **Dynamic Entity Movement:** Drones, humans, and cars move within the simulation, following specific behavior patterns.
- **Package Delivery System:** Drones simulate the process of picking up and delivering packages amidst various challenges.
- **Package Stealing Ability:** Car pirates can intercept and steal packages, adding complexity to the drone deliveries.
- **Real-Time Notifications:** Uses the Observer Pattern to inform users of significant events like drone progress, human movements, and car actions, displayed on a notification bar.
- **Interactive User Interface:** Provides a platform for users to observe and interact with the simulation.

### **New Features - State Pattern Implementation and Notification Bar:**

#### **What do they do?**
- **State-Based Behaviors:** Introduces states for drones, humans, and car pirates. Drones have states like 'Available', 'Picking Up', and 'Delivering'. Humans switch between 'Looking' and 'Found', while car pirates transition through 'Available', 'Picking Up', and 'Success'.
- **Notification Bar:** Implements the Observer Pattern to display real-time notifications in the simulation's UI, including detailed steps of drone, human, and car pirate actions.

#### **Why are they significantly interesting?**
These features introduce a dynamic and strategic element to the simulation, reflecting the complexity of real-world interactions and challenges in drone delivery systems.

#### **How do they add to the existing work?**
They enhance the simulation's realism and educational value, allowing users to observe and understand the adaptive behaviors and interactions among different entities.

#### **Design Pattern Implementation:**
- The State Pattern is used for dynamic behavior changes in entities, perfect for scenarios where objects must adapt their actions based on internal states.
- The Observer Pattern is implemented in the notification bar, efficiently broadcasting updates on entity activities to the users.

#### **Instructions for the New Features:**
- **State-Based Behaviors:** Watch how humans, drones, and car pirates change their actions as they transition between states.
- **Notification Bar:** View the notification bar for live updates on entity activities. This feature operates automatically as part of the simulation.
