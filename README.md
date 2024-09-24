## Overview
**OffsetPointer** is a C++ library that provides an implementation of an offset-based smart pointer. Unlike traditional pointers that store absolute memory addresses, 'OffsetPtr' stores offset relative to a base address.
This design is particularly useful in scenarios where memory addresses can vary across different environment or sessions, such as shared memory or memeory-mapped files.
