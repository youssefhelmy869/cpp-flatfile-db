A lightweight, file-backed flat-file database engine written from scratch in modern C++. This project implements custom parsing, record indexing, and complete CRUD operations with persistent text-file storage, demonstrating foundational systems programming and object-oriented design concepts.

## Features ✨

* **Persistent Storage:** Automatically saves, updates, and syncs database records and field schemas to flat text files.
* **Full CRUD Operations:** Supports creating databases, inserting records, searching via single/multiple fields, updating records, and deleting rows with dynamic index re-alignment.
* **$O(1)$ Record Lookups:** Uses internal vector index mapping to locate records instantly by their unique system index.
* **Robust Error Handling:** Utilizes C++ standard exceptions (`std::invalid_argument`, `std::runtime_error`) to catch schema mismatches, missing files, and out-of-bounds queries safely.
* **Custom Serialization Engine:** Parses and serializes pipe-delimited (`|`) rows and metadata without relying on external third-party database libraries.

---

## Architecture & Design 📐

The engine is built around two primary components:
1. **`record` Struct:** Manages individual rows of data, enforces field consistency, and handles data export/import workflows. *(Note: Copy and move semantics are explicitly deleted to enforce safe resource management).*
2. **`database` Class:** Manages file streams (`std::fstream`), schema definitions, record collections, file synchronization (`update_file`), and field-based searching (`find_index`, `find_all_index`).

---

## Getting Started 🚀

### Prerequisites
* A C++ compiler supporting C++11 or higher (e.g., GCC, Clang, MSVC).

### Compilation & Execution
Clone the repository and compile using your preferred toolchain (such as GCC via MinGW/MSYS2):