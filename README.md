# Airdrop Software

![License: GPL v3](docs/README.assets/License-GPLv3-blue.svg)(https://www.gnu.org/licenses/gpl-3.0)![](README.assets/pipeline.svg)

![Wall-E / 1920x1080 Wallpaper | Wall e, Animated movies, Animation movie](docs/README.assets/051db99b019d8ab861c87ac76c04ed81.jpg)

---

## Table of Content

- [Airdrop Software](#airdrop-software)
  - [Table of Content](#table-of-content)
  - [Introduction](#introduction)
  - [Development](#development)
    - [Workflow](#workflow)
    - [Design](#design)
    - [Code Style Guide](#code-style-guide)
  - [Installation](#installation)
    - [Build](#build)
    - [Run](#run)
    - [Test](#test)
      - [Software testing](#software-testing)
      - [HITL(Hardware in the loop)](#hitlhardware-in-the-loop)
      - [SITL(Software in the loop)](#sitlsoftware-in-the-loop)
  - [Debug](#debug)
  - [FAQ](#faq)
  - [Change log](#change-log)
    - [v1.0](#v10)

## Introduction

Welcome to UAV Airdrop software! We are the subteam in [UBC UAS](www.ubcuas.com) that is responsible for the Airdrop task section of the [AUVSI compeition](https://www.auvsi-suas.org/). This document will introduce you to our system and how we develop it, hopeful give you some insight on the project, as well as contributing to it as soon as possible.  



## Development 

### Workflow

We use [Trello](https://trello.com/b/pWR6ylrp) for project managing. The detailed sprint and tasks are on the Trello board, and we will use them to list out detailed description of the task, subtasks, assignee of the task, due date and checklist. Please refer to the Trello board for your tasks frequently for updates. If you don't have access to this board, please ask your subteam lead to add you to it. 

Please refer to [Work flow](docs/WORK_FLOW.md) for how we use git for version control. 

### Design

If you are interested in our software and hardware system design, please refer to [design](docs/DESIGN.md)

### Code Style Guide

If you are curious about what our coding convention is, what coding style is acceptable or what's the preferred OOP standard, please see [Style Guide](docs/CODE_STANDARD.md)



## Installation

Supported OS: Window, MacOS, Linux

Software Checklist

- [vscode](https://code.visualstudio.com/download)
- [webots](https://www.cyberbotics.com/)
- [platformio](https://platformio.org/platformio-ide)
  - might require `python3` installed

Others

- usb driver is  (on linux, please check `lsusb`)

### Build

TBC

### Run

TBC



### Test

#### Software testing

#### HITL(Hardware in the loop)

#### SITL(Software in the loop)

Our software in the loop testing will use Webots as the simulation environment. Webots will replace the physical robot, simulate it's behaviour, and provides simulated sensor data based on the state of the robot. 

Please refer to [Simulation](simulation/README.md)



## Debug

TBC



## FAQ

If you have any questions, see [FAQ](docs/FAQ.md)!



## Change log

### v1.0 

- first draft of the readme
- added simulation readme, code standard
- complete development section
- complete installation section



