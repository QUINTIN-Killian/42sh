# 42sh

A robust C-based implementation of a Unix shell inspired by tcsh, providing a command-line interface for process management and system interaction.

---

## 🧠 Description

This project focuses on recreating the user-facing functionality of a standard Linux terminal. The software serves as an intermediary between the user and the operating system, capable of interpreting commands, managing environment variables, and organizing complex execution flows through a command-line prompt.

User Features

- Command Execution: Launching system binaries and managing their lifecycle from the prompt.
- Stream Redirection: Directing input and output between files and processes using standard operators.
- Pipeline Management: Connecting multiple commands to allow data to flow seamlessly from one task to the next.
- Built-in Commands: A suite of internal tools for navigating the file system and managing the user session.

Interaction Logic

- Environment Handling: Storing and retrieving configuration variables that define the user's workspace.
- Command History: Tracking previously entered instructions for quick recall and efficiency.
- Signal Management: Gracefully handling user interruptions and process terminations to maintain shell stability.

---

## 🚀 Getting started

### Installing

**Clone the repository:**

```bash
git clone https://github.com/QUINTIN-Killian/42sh.git
cd 42sh
```

### Executing program

**Compiling:**

```bash
make
```

**Executing:**

```bash
./42sh
```

---

## 👥 Authors

* [@Killian QUINTIN](https://github.com/QUINTIN-Killian)
* [@Florian RENAUD](https://github.com/FLOWleplusbeau)
* [@William JOLIVET](https://github.com/WilliamJlvt)
* [@Max ROBERT](https://github.com/MaxxRobert)
* [@Laurent GONZALES](https://github.com/lg-epitech)
