# Airdrop Software

![License: GPL v3](docs/README.assets/License-GPLv3-blue.svg)![](https://gitlab.com/ubcuasinfo/airdrop-software-2020/badges/master/pipeline.svg)

![Wall-E / 1920x1080 Wallpaper | Wall e, Animated movies, Animation movie](docs/README.assets/051db99b019d8ab861c87ac76c04ed81.jpg)
---

<!-- vscode-markdown-toc -->
* 1. [Introduction](#Introduction)
* 2. [Development](#Development)
	* 2.1. [Workflow](#Workflow)
	* 2.2. [Design](#Design)
	* 2.3. [Code Style Guide](#CodeStyleGuide)
* 3. [Installation](#Installation)
	* 3.1. [Build](#Build)
	* 3.2. [Run](#Run)
	* 3.3. [Test](#Test)
		* 3.3.1. [Software testing](#Softwaretesting)
		* 3.3.2. [HITL(Hardware in the loop)](#HITLHardwareintheloop)
		* 3.3.3. [SITL(Software in the loop)](#SITLSoftwareintheloop)
* 4. [Debug](#Debug)
* 5. [FAQ](#FAQ)
* 6. [Change log](#Changelog)
	* 6.1. [v1.0](#v1.0)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->


##  1. <a name='Introduction'></a>Introduction

Welcome to UAV Airdrop software! We are the subteam in [UBC UAS](www.ubcuas.com) that is responsible for the Airdrop task section of the [AUVSI compeition](https://www.auvsi-suas.org/). This document will introduce you to our system and how we develop it, hopeful give you some insight on the project, as well as contributing to it as soon as possible.  

```mermaid
gantt
    title Timeline
    dateFormat  YY-MM-DD

    section Design
    Proposal            :done,    des1, 20-09-26,20-10-03
    Design review 1            :done,  des2, 20-10-03, 20-10-17
    System design               :active,         des3, after des2, 3w
    Design review 2              :         des4, after des3, 1w

    section Implementation
    Divide tasks into modules :crit, done, imp1, 20-10-17,7d
    Deliver modules          :crit, done, after imp1, 7d
    Working on modules             :crit, active, imp2, after imp1, 3w
   	Submodule testing        :crit, after imp2, 2w

    section Simulator Testing
    Simulator set up               :done, s1, after des1, 1w
    Simulator controller testing      :active, s2, after des2  , 3w
    Simulator logic testing    :crit, doc1, after s2  , 3w

    section Integration
    Software integration test               :after doc1, 2w
    Hardware Integration test				: 1w
	System integration test					: 2w
```


##  2. <a name='Development'></a>Development 

###  2.1. <a name='Workflow'></a>Workflow

We use [Trello](https://trello.com/b/pWR6ylrp) for project managing. The detailed sprint and tasks are on the Trello board, and we will use them to list out detailed description of the task, subtasks, assignee of the task, due date and checklist. Please refer to the Trello board for your tasks frequently for updates. If you don't have access to this board, please ask your subteam lead to add you to it. 

Please refer to [Work flow](docs/WORK_FLOW.md) for how we use git for version control. 

###  2.2. <a name='Design'></a>Design

If you are interested in our software and hardware system design, please refer to [design](docs/DESIGN.md)

###  2.3. <a name='CodeStyleGuide'></a>Code Style Guide

If you are curious about what our coding convention is, what coding style is acceptable or what's the preferred OOP standard, please see [Style Guide](docs/CODE_STANDARD.md)



##  3. <a name='Installation'></a>Installation

Supported OS: Window, MacOS, Linux

Software Checklist

- [vscode](https://code.visualstudio.com/download)
- [webots](https://www.cyberbotics.com/)

VSCode plugins
- [platformio](https://platformio.org/platformio-ide)
  - might require `python3` installed
- [live share](https://visualstudio.microsoft.com/services/live-share/)
  - require gitlab/microsoft login
- [clang-format](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format)

Others
- usb driver is updated (on linux, please check `lsusb`)

###  3.1. <a name='Build'></a>Build

TBC

###  3.2. <a name='Run'></a>Run

TBC


###  3.3. <a name='Test'></a>Test

####  3.3.1. <a name='Softwaretesting'></a>Software testing

####  3.3.2. <a name='HITLHardwareintheloop'></a>HITL(Hardware in the loop)

####  3.3.3. <a name='SITLSoftwareintheloop'></a>SITL(Software in the loop)

Our software in the loop testing will use Webots as the simulation environment. Webots will replace the physical robot, simulate it's behaviour, and provides simulated sensor data based on the state of the robot. 

Please refer to [Simulation](simulation/walle/README.md)



##  4. <a name='Debug'></a>Debug

TBC



##  5. <a name='FAQ'></a>FAQ

If you have any questions, see [FAQ](docs/FAQ.md)!



##  6. <a name='Changelog'></a>Change log

###  6.1. <a name='v1.0'></a>v1.0 

- first draft of the readme
- added simulation readme, code standard
- complete development section
- complete installation section



