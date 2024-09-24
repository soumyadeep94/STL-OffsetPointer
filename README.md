## Overview
**OffsetPointer** is a C++ library that provides an implementation of an offset-based smart pointer using STL. Unlike traditional pointers that store absolute memory addresses, 'OffsetPtr' stores offset relative to a base address. It is inspired by Boost's ´offset_ptr´ from the [Boost.interprocess](https://www.boost.org/doc/libs/1_85_0/boost/interprocess/offset_ptr.hpp) library.
This design is particularly useful in scenarios where memory addresses can vary across different environment or sessions, such as shared memory or memeory-mapped files.

##Features

- **Relative Addressing:** Stores pointers as offsets relative to a base address, enhancing portability.
- **Thread-Safe:** Utilizes 'std::atomic' for safe concurrent access.
- **Lightweight:** Minimal overhead comapred to raw pointers.
- **Serialization-Friendly:** Offsets are easier to serialize compared to absolute pointers.
- **Easy Integration:** Seamlessly integrates with existing C++ projects.

## Why OffsetPointer?

Traditional pointers can pose challenges in cerrtain environments:
- **Shared Memory:** Absolute addresses can differ between processes, making raw pointers unreliable.
- **Memory-Mapped Files:** Addresses can vary each time the file is mapped, leading to invalid references when working with absolute memory addresses.
- **Persistent Data Structures:** Storing absolute pointers in persistent storage can cause issues when adddresses change across sessions.
