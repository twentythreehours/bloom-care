# Bloom Care

# Core Concept

### Project Summary

**Bloom Care** is a wearable biosensor system that transforms women's physiological and emotional data into unique generative flowers, encouraging self-care through real-time data visualization and interactive digital art.

### Overview

Bloom Care combines an Arduino/ESP32-based wearable biosensor, a mobile companion app, and a real-time generative art experience.

The wearable device continuously collects physiological signals throughout different stages of the menstrual cycle, while the mobile app allows users to record their mood, healthy activities, and personal reflections. Using this personal data, Bloom Care generates a unique digital flower that grows and changes in real time.

Rather than simply visualizing health metrics, Bloom Care transforms invisible physiological changes into an emotional and artistic experience. Each flower reflects the user's current physical condition and emotional state, helping them better understand their bodies throughout the menstrual cycle.

By nurturing their digital flower, users are encouraged to develop healthier habits and greater self-awareness. A flourishing flower celebrates physical well-being, while a struggling flower gently reminds users to pay more attention to their bodies and practice self-care.


---

# System Architecture

The system consists of three major components:

1. **Data Collection (Hardware)** — Arduino / ESP32 wearable biosensor
2. **Data Input & Storage** — Mobile App
3. **Generative Visualization** — p5.js

---

# Data Collection

## Automatic Collection (Hardware)

The wearable device continuously collects physiological signals, including:

* Heart rate
* Blood oxygen (SpO₂)
* Skin temperature
* Physical activity level

These measurements are collected throughout the user's menstrual cycle and streamed to the mobile app via Bluetooth.

## Manual Input (Mobile App)

Users can also record:

* Daily mood (1–10 rating)
* Healthy activities, such as:

  * Reading
  * Meditation
  * Exercise
* Personal notes or memorable events of the day

---

# User Experience

## Step 1 — Collect Physiological Data

Throughout the day, the wearable device continuously monitors physiological signals.

The collected data is synchronized with the mobile application in real time through Bluetooth.

---

## Step 2 — Daily Check-in

Users open the app at any time during the day to:

* Automatically record the current menstrual cycle phase
* Log their daily mood
* Record healthy activities
* Write memorable moments or personal reflections

---

## Step 3 — Real-time Flower Generation

Each flower begins as a seed and gradually grows into a unique digital flower based on the user's physiological and emotional data.

### Flower Structure

Each flower's fundamental form is inspired by one of three structures of the female reproductive system:

* Uterus
* Corpus uteri
* Ovum

Different menstrual phases determine the flower's basic morphology.

### Visual Mapping

The flower changes according to the following rules:

| Data                                | Visual Effect                                 |
| ----------------------------------- | --------------------------------------------- |
| Higher heart rate                   | Faster pulsing animation in the flower center |
| Higher blood oxygen (SpO₂)          | Richer and more saturated colors              |
| Higher skin temperature             | Color palette shifts toward warmer hues       |
| Lower physical activity (more rest) | Fuller, more open blossoms                    |

### Emotional Influence

Mood further adjusts the flower's appearance:

* Positive mood → adds warmer color tones
* Negative mood → adds cooler color tones

### Healthy Activities

When users complete healthy activities such as reading, meditation, or exercise, the flower grows taller, symbolizing positive self-care.

---

## Step 4 — Personal Flower Garden

Every generated flower is automatically saved to the user's calendar.

Users can:

* Browse flowers from previous dates
* Observe long-term physical and emotional trends
* Read past journal entries and notes
* Share screenshots of their personal flower garden

---

# Design Philosophy

Bloom Care is designed to make invisible physiological changes visible through generative art.

When users notice that their flower appears less healthy, they are encouraged to pay closer attention to their physical and emotional well-being. As they develop healthier habits, their flower gradually becomes more vibrant.

Likewise, seeing a flourishing flower serves as a reminder that their body is healthy, resilient, and beautiful.

The project aims to foster long-term self-awareness and self-care rather than focusing solely on numerical health metrics.

---

# Technical Implementation

## Hardware

* Arduino / ESP32 wearable biosensor
* Physiological sensor integration
* Real-time physiological signal acquisition

---

## Data Transmission

* Bluetooth communication between ESP32 and the mobile app
* Real-time data synchronization

---

## Mobile App

### Frontend

The application contains three primary pages:

### Home

* Displays today's flower
* Allows users to record mood
* Record healthy activities
* Write daily notes

### Calendar

* Displays every generated flower
* Allows users to revisit previous flowers

### Profile

* User profile and personal information

---

### Flower Rendering Workflow

The flower is rendered in two stages:

1. **Initial Rendering**

   * After physiological data has been received and synchronized.

2. **Final Rendering**

   * After the user submits mood, activities, and journal entries.

Once the second rendering is completed, the flower remains fixed for that day.

The mobile app embeds a **WebView**, which loads a **p5.js** sketch responsible for rendering the generative flower.

---

### Backend

Responsible for:

* Bluetooth communication
* Receiving sensor data
* Parsing physiological signals
* Passing processed data to the WebView

---

### Database

Stores:

* Physiological history
* Mood records
* Daily activities
* Personal notes
* Historical flower data

---

# Technology Stack

* Arduino
* ESP32
* Bluetooth Low Energy (BLE)
* Flutter
* Dart
* WebView
* p5.js
* Database
* Figma
* GitHub

---

# Future Learning

* p5.js
* Arduino & ESP32 development
* Flutter + Dart
* Bluetooth Low Energy (BLE)
* WebView integration
* Database design
* UI/UX design with Figma
* GitHub collaboration

---

# Responsibilities

* Hardware development
* Sensor integration
* Mobile app UI/UX design
* Real-time generative flower visualization using p5.js
* App backend development
* Bluetooth communication
* Database integration
* GitHub project deployment and maintenance
