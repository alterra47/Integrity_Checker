# IntegrityChecker: Hybrid C++/Python File Hashing Service

## 1. Project Overview
IntegrityChecker is a full-stack security tool designed to demonstrate high-performance systems programming integrated with modern web technologies. It offloads computationally intensive cryptographic operations (SHA-256) to a custom C++ microservice, while utilizing Python (FastAPI) for API management and file handling.

### Architecture
* **Frontend:** HTML5, CSS3, Vanilla JavaScript (Dark Mode UI)
* **Backend:** Python 3.10+, FastAPI, Uvicorn
* **Compute Engine:** C++17, Custom TCP Socket Server, Raw SHA-256 Implementation
* **IPC Protocol:** JSON over TCP Sockets (Localhost:8080)

## 2. Directory Structure
```text
/
├── cpp_service/      # The C++ High-Performance Worker
│   ├── src/          # Source code (Server, Hasher, SHA256)
│   └── CMakeLists.txt
├── py_backend/       # The Python API Manager
│   ├── static/       # Frontend Assets
│   └── main.py       # FastAPI Application
└── docs/             # Design Documents
