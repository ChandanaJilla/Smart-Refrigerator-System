# Smart Refrigerator System

The Smart Refrigerator System is a cost-effective solution to transform an existing refrigerator into a smart refrigerator, providing users with the benefits of advanced features without the need to purchase an expensive appliance.

## Introduction

In today's fast-paced world, where time is of the essence, it is crucial to have efficient and intelligent appliances that can simplify our daily lives. Smart refrigerators have gained popularity for their convenience and advanced features, but they often come with a hefty price tag. The Smart Pantry System aims to bridge this gap by retrofitting existing refrigerators with smart functionality.

The main objective of this project is to enhance the user experience and improve food management through the implementation of a smart pantry system. The system utilizes sensors, microcontrollers, and wireless communication modules to provide real-time monitoring and notifications.

## Key Features

- Food spoilage detection using an MQ2 sensor: The system can detect changes in the environment and alert the user if food spoilage is detected.
- Smart pantry level monitoring using load cells: Load cells are used to measure the weight of food items in the pantry, allowing users to monitor stock levels and receive notifications when supplies are running low.
- Instant photo notifications: The system captures images of the pantry contents using an ESP32 camera and sends instant photo notifications to the user's email, providing a visual update of the pantry status.

## Tools and Technologies

The Smart Refrigerator System is built using the following tools and technologies:

- Microcontrollers: Arduino or Raspberry Pi
- Sensors: MQ2 sensor for food spoilage detection, load cells for pantry level monitoring
- ESP32 Camera: Captures images of the pantry contents
- ESP8266 Wi-Fi Module: Enables wireless communication and connectivity for sending notifications
- Programming Languages: Arduino programming language (based on C/C++) or Python
- Libraries and Frameworks: Platform-specific libraries for sensor integration, communication, and image processing
- Wireless Communication: Wi-Fi for internet connectivity
- Image Processing: Libraries such as OpenCV for image analysis and object detection
- Email Service: Integration with an email service provider for sending instant photo notifications

## Installation and Setup

1. Clone the repository: `git clone https://github.com/ChandanaJilla/Smart-Refrigerator-System.git`
2. Install the necessary libraries and dependencies as specified in the project documentation.
3. Connect the hardware components according to the provided circuit diagram.
4. Upload the firmware to the microcontroller.
5. Configure the Wi-Fi settings and email credentials in the project configuration files.
6. Power on the system and ensure all components are functioning correctly.

## Usage

1. Access the web interface or mobile app (if applicable) to monitor the smart pantry system.
2. Receive instant photo notifications via email when the system detects changes in the pantry or detects potential food spoilage.
3. Use the monitoring features to keep track of pantry stock levels and plan grocery shopping accordingly.

