# Core Concept

This project combines physiological data collected through Arduino-based sensors with an app that records users' emotions and menstrual cycle information. Using this personal data, the system generates a unique digital flower in real time, encouraging girls to care for themselves just as they would nurture a flower.

---

# System Architecture

1. **Data Collection (Hardware):** Arduino
2. **Data Input & Storage:** Mobile App
3. **Generative Art:** p5.js

---

# Data Sources (Collected Daily During the Menstrual Cycle)

### Automatic Collection (Hardware)

* Average heart rate
* Sleep quality (measured by nighttime activity)
* Skin oil secretion (measured through skin conductivity)

### Manual Input (Mobile App)

* Daily mood (rated from 1–10)
* Healthy activities completed:

  * Reading
  * Meditation
  * Exercise

---

# Interaction Flow

## 1. Morning / Daytime

The Arduino device collects physiological data.

* The collected data is synchronized with the mobile app in real time via Bluetooth.

## 2. Anytime / Evening

Users open the app to complete their daily check-in.

* The current menstrual cycle phase is automatically recorded.
* Users log their daily mood.

## 3. Flower Visualization

The flower begins as a seed and gradually evolves based on the user's personal data.

### (1) Color Logic

**Base Color (Menstrual Phase)**

* Menstruation → Red palette
* Luteal phase → Pink palette
* Follicular phase → Purple palette
* Ovulation → Yellow palette

*(Specific colors can be refined later.)*

**Mood Influence**

* Positive mood → Adds warm tones
* Negative mood → Adds cool tones

**Final Flower Color**

* A blend of the menstrual phase color and mood-based color.

### (2) Morphology Logic

* **Better sleep quality**

  * More petals
  * Fuller shape
  * More open and expanded petals

* **Higher skin oil secretion**

  * Increased petal glossiness (adjusting saturation and shine)

* **Heart rate**

  * The flower's center gently pulses in sync with the user's heart rate.

* **Healthy activities**

  * When users record activities such as reading, meditation, or exercise, the flower grows taller.

---

## 4. Mobile App Features

* Each day's generated flower is automatically saved to a calendar, allowing users to observe changes over time.
* Users can share screenshots of their personal flower garden.

---

# Technical Implementation

## Hardware

* Arduino-based physiological sensing device

## Data Transmission

* The ESP32 sensor transmits physiological data to the app via Bluetooth.

## Mobile App

### (1) Frontend

The app consists of three main pages:

* **Home Page**

  * Displays today's flower.
  * Allows users to record their mood and healthy activities.

* **Calendar Page**

  * Displays all previously generated flowers in a calendar view.

* **Profile Page**

  * Contains the user's basic information.

### Flower Rendering Workflow

The flower is rendered twice:

1. **First Render**

   * After the previous day's physiological data has been successfully synchronized.

2. **Second Render**

   * After the user submits their daily mood and activities.
   * The flower remains unchanged for the rest of the day.

A **WebView** component is embedded within the app to load the **p5.js** sketch, where the flower is rendered dynamically.

### (2) Backend

* Bluetooth connection management
* Sensor data reception
* Data parsing
* Passing processed data to the WebView

### (3) Database

* Stores users' historical physiological and emotional data.

---

# Technologies to Learn

1. p5.js
2. Arduino
3. Flutter + Dart + WebView (App Development)
4. Figma
5. GitHub
6. Database Design & Management

---

# Responsibilities

* Hardware development
* Mobile app UI/UX design
* Real-time flower generation with p5.js
* App backend development
* GitHub project deployment and maintenance
