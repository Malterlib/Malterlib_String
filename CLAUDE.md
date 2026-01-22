# CLAUDE.md - String Module

## Module Overview

The String module provides comprehensive string handling capabilities for the Malterlib framework, supporting multiple character encodings (ANSI, UTF-8, UTF-16, UTF-32/Unicode) with efficient algorithms and flexible storage implementations. This module offers high-performance string operations, formatting, parsing, and Unicode support.

## Key Components

### Core String Types
- **CStr** - UTF-8 string (most common, default)
- **CStrAnsi** - ANSI/ASCII string (single-byte, no Unicode)
- **CWStr** - UTF-16 string (Windows wide string compatible)
- **CUStr** - UTF-32/Unicode string (full Unicode codepoint per character)
- **gc_Str** - Compile-time constant strings (constexpr)

### String Variants
- **NonTracked** variants - No memory tracking (e.g., `CStrNonTracked`)
- **Secure** variants - Secure memory wiping (e.g., `CStrSecure`)
- **VMem** variants - Virtual memory backed strings
- **Span** types - Non-owning string views (e.g., `CStrSpan`)

### Storage Implementations
- **Dynamic** (`TCStrImp_Dynamic`) - Heap-allocated, growable
- **Fixed** (`TCStrImp_Fixed`) - Stack-allocated, fixed size
- **Pointer** (`TCStrImp_Pointer`) - References external memory
- **Virtual** (`TCStrImp_Virtual`) - Abstract interface for custom storage

### Algorithms
Extensive algorithm library with modular design:
- **Text Operations**: Find, Replace, Split, Trim, Capitalize, Case conversion
- **Comparison**: Compare, StartsWith, EndsWith, WildcardMatch
- **Encoding**: UTF-8/16/32 conversion, ANSI conversion
- **Hashing**: DJB2, Murmur3, SDBM algorithms
- **Special**: FuzzyMatch, Escape (Bash), Sanitize

### Formatting & Parsing
- **Formatters**: Integer, Float, Binary, Time, String formatting
- **Parsers**: Integer, Float, String parsing with pattern matching
- **Format Utils**: Printf-style formatting with type safety

### Iterators
- **Character Iterators**: Navigate by characters/codepoints
- **Unicode Iterator**: Proper Unicode grapheme cluster iteration
- **UTF Encode Iterators**: Convert between encodings during iteration
- **Output Iterators**: Write encoded data during iteration

## Module-Specific Conventions

### Namespace Organization
- Primary namespace: `NMib::NStr`
- System integration: `NMib::NSys::NStr`
- Private implementations: `NMib::NStr::NPrivate`

### Naming Patterns
- String classes: `C[Encoding]Str[Variant]` (e.g., `CStr`, `CWStrSecure`)
- Template classes: `TC[Component]` (e.g., `TCStr`, `TCFormat`)
- String traits: `CStrTraits_[Type]` (e.g., `CStrTraits_CStr`)
- Algorithms: Direct names (e.g., `Find`, `Replace`, `Trim`)
- Character types: `ch8`, `ch16`, `ch32` (signed), `uch8`, `uch16`, `uch32` (unsigned)

### Character Type System
```cpp
// Signed character types
ch8  - UTF-8/ANSI character
ch16 - UTF-16 character
ch32 - UTF-32/Unicode codepoint

// Unsigned variants
uch8, uch16, uch32

// Zero-on-destruction variants (secure)
zuch8, zuch16, zuch32
```

### String Type Encoding
```cpp
enum EStrType {
    EStrType_Ansi,    // Single-byte ANSI/ASCII
    EStrType_Unicode, // Full Unicode (UTF-32)
    EStrType_UTF,     // Variable-width UTF (8 or 16)
    EStrType_Undefined
};
```

## Dependencies

### Internal Malterlib Modules
- **Core** - Basic types and platform abstractions
- **Container** - Vector for string storage
- **Memory** - Allocator interfaces
- **Algorithm** - Sorting and searching primitives
- **Iterator** - Iterator base classes
- **Encoding** - Character encoding conversions

## Architecture Details

### String Storage Architecture
```cpp
// Strings use template-based storage implementations
template <typename t_CStrTraits>
class TCStr {
    // Storage delegated to implementation class
    typename t_CStrTraits::CImpl m_Impl;
};

// Dynamic implementation example
template <typename t_CStrTraits>
class TCStrImp_Dynamic {
    ch8* m_pData;
    mint m_Capacity;
    mint m_Length;
};
```

### Algorithm Modular Design
Each algorithm is in a separate header for compilation efficiency:
- `Malterlib_String_Algorithm_[Name].h` - Interface
- `Malterlib_String_Algorithm_[Name].hpp` - Implementation

### Format System
```cpp
// Type-safe formatting with compile-time checking
auto Result = "Value: {}, Float: {}"_f << 42 << 3.14f;

// Or using CFormat directly
CStr Result2 = CStr::CFormat("Value: {}, Float: {}") << 42 << 3.14f;
```

### Unicode Support
- Full Unicode support with proper grapheme cluster handling
- Automatic encoding conversion between string types
- Iterator-based encoding transformation
- Normalization and case folding support

## Common Tasks

### Basic String Operations
```cpp
CStr Str("Hello World");
Str.f_Replace("World", "Malterlib");
Str.f_ToUpperCase();

if (Str.f_StartsWith("HELLO")) {
    auto Pos = Str.f_Find("MALTERLIB");
}
```

### String Formatting (Three Variants)

#### 1. CFormat - Object-based formatting
```cpp
// Create formatted string directly
CStr Formatted = CStr::CFormat("Value: {}") << 42;

// Multiple values
CStr UserInfo = CStr::CFormat("User: {}, ID: {}") << Username << UserID;

// With format specifiers
CStr HexFormat = CStr::CFormat("{nh}") << 255;  // Outputs hex without 0x prefix

// Format into existing string by concatenation
CStr Result;
Result += CStr::CFormat("Temperature: {}°C") << Temperature;
```

#### 2. User-defined literal _f - Concise inline formatting
```cpp
// Using the _f suffix for format strings
auto Result = "User: {}, ID: {}"_f << Username << UserID;

// Works with different string types
auto WideResult = u"Value: {}"_f << 42;      // UTF-16
auto UnicodeResult = U"Value: {}"_f << 42;    // UTF-32

// In test paths and debugging
DMibTestPath("{}"_f << TestValue);
```

#### 3. fg_Format - Function-based formatting
```cpp
// Generic format function
CStr Result = fg_Format("Temperature: {}°C", Temperature);

// Format with specific return type
CWStr WideResult = fg_Format<CWStr>("Value: {}", Value);

// Used with format modifiers
auto HexStr = fg_Format("Hex: {}", fg_FormatIntFormat<16>(255));

// Format integer with specific radix
auto Binary = fg_Format("Binary: {}", fg_FormatIntFormat<2>(42));
```

### Parsing
```cpp
// Parse with format string
CStr Input("42 3.14 Hello");
int32 IntVal;
float FloatVal;
CStr StrVal;

aint nParsed = 0;
(CStr::CParse("{} {} {}") >> IntVal >> FloatVal >> StrVal).f_Parse(Input, nParsed);

// Parse with delimiters
CStr String1, String2, String3;
(CStr::CParse("{}...{}...{}") >> String1 >> String2 >> String3).f_Parse("Test1...Test2...Test3", nParsed);

// Parse escaped strings
CStr QuotedStr;
(CStr::CParse("{se}") >> QuotedStr).f_Parse("\"Hello World\"", nParsed);  // {se} = string escaped
```

### Encoding Conversion
```cpp
CStr UTF8String("Hello 世界");
CWStr UTF16String = UTF8String;  // Automatic conversion
CUStr UnicodeString = UTF8String;  // Full Unicode

// Manual conversion
CAnsiStr AnsiStr;
fg_SystemEncodeAnsiStr(UTF8String, AnsiStr, '?'); // '?' for unmappable chars
```

### Using Different Storage
```cpp
// Fixed-size stack string
TCStrFixed<256> StackStr("Stack allocated");

// Secure string (wiped on destruction)
CStrSecure Password("secret");

// String span (non-owning view)
CStrSpan View(SomeString.f_GetArray(), SomeString.f_GetLen());

// Compile-time constant strings
constexpr auto& MyConstStr = gc_Str<"Compile-time constant">.m_Str;  // CStr const
constexpr auto& MyWideStr = gc_Str<str_utf16("Wide string")>.m_Str;  // CWStr const
constexpr auto& MyUnicodeStr = gc_Str<str_utf32("Unicode")>.m_Str;   // CUStr const

// Interoperability with runtime strings
CStr RuntimeStr = gc_Str<"Hello">.m_Str;  // Seamless usage
RuntimeStr += " World";

// Same gc_Str instance across translation units (singleton)
auto& ConstRef1 = gc_Str<"Same">.m_Str;
auto& ConstRef2 = gc_Str<"Same">.m_Str;  // Same address as ConstRef1
```

### Wildcard Matching
```cpp
// Function returns EMatchWildcardResult enum
if (NStr::fg_StrMatchWildcard(Filename, "*.txt") == NStr::EMatchWildcardResult_WholeStringMatchedAndPatternExhausted) {
    // Process text file
}

// Wildcard patterns:
// ? - matches single character
// * - matches zero or more characters
auto Result = NStr::fg_StrMatchWildcard("test.txt", "*.txt");
auto Result2 = NStr::fg_StrMatchWildcard("file123.doc", "file???.doc");
```

### Running Module Tests
```bash
# Build tests
MalterlibBuildShowProgress=false ./mib build Tests

# Run all string tests
/opt/Deploy/Tests/RunAllTests --paths '["Malterlib/String/*"]'

# Run specific algorithm tests
/opt/Deploy/Tests/RunAllTests --paths '["Malterlib/String/Algorithm/Compare", "Malterlib/String/Algorithm/Find"]'

# Run format/parse tests
/opt/Deploy/Tests/RunAllTests --paths '["Malterlib/String/Container/Format/*", "Malterlib/String/Container/Parse"]'
```

## Important Files

### Headers (Public API)
- `Include/Mib/String/String` - Main string classes
- `Include/Mib/String/Algorithm` - Algorithm interfaces
- `Include/Mib/String/Formatters/*` - Formatting components
- `Include/Mib/String/Parsers/*` - Parsing components
- `Include/Mib/String/Implementations/*` - Storage implementations

### Core Implementation
- `Source/Malterlib_String.h/cpp` - Main string implementation
- `Source/Malterlib_String_Container.h/cpp` - Container base
- `Source/Malterlib_String_Types.h` - Type definitions and traits

### Algorithms
- `Source/Malterlib_String_Algorithm_*.h/hpp` - Individual algorithms
- `Source/Malterlib_String_Algorithm_Common.h` - Shared algorithm code

### Storage Implementations
- `Source/Malterlib_String_Container_Imp*.h` - Storage backends
- Dynamic, Fixed, Virtual, Pointer implementations

### Formatting & Parsing
- `Source/Malterlib_String_Container_Format_*.h` - Formatters
- `Source/Malterlib_String_Container_Parse_*.h` - Parsers
- `Source/Malterlib_String_FormatUtils.h/hpp` - Format utilities

### Unicode & Encoding
- `Source/Malterlib_String_Iterator_Unicode.h/hpp` - Unicode iteration
- `Source/Malterlib_String_Iterator_UTF*.h/hpp` - UTF encoding iterators
- `Source/Malterlib_String_UnicodeConversion.h` - Conversion utilities
- `Source/Malterlib_String_AnsiConversion.h` - ANSI conversion

### Special Features
- `Source/Malterlib_String_FuzzyMatch.h/cpp` - Fuzzy string matching
- `Source/Malterlib_String_MultiReplace.h/hpp` - Batch replacements
- `Source/Malterlib_String_Appender.h/hpp` - Efficient string building

## Module-Specific Notes

### Performance Characteristics
- **Small String Optimization** (SSO) in dynamic implementation
- **Copy-on-Write** (COW) for efficient string copies
- **Algorithm complexity**:
  - Find/Replace: O(n*m) worst case, optimized for common cases
  - Hash functions: O(n) with good distribution
  - Case conversion: O(n) with Unicode support
  - Wildcard match: O(n*m) with optimization for simple patterns

### Character Encoding
- UTF-8 is default and recommended for most use cases
- UTF-16 for Windows API compatibility
- UTF-32 when direct codepoint access needed
- ANSI for legacy system compatibility
- Automatic conversion between types with potential data loss warnings

### Memory Management
- Dynamic strings use exponential growth (typically 1.5x)
- NonTracked variants bypass memory tracking system
- Secure variants clear memory on destruction
- Fixed variants never allocate heap memory

### Thread Safety
- String objects are NOT thread-safe for modification
- Read-only access from multiple threads is safe
- Use synchronization for concurrent modifications
- Consider thread-local strings for performance

### Unicode Considerations
- Full Unicode 15.0 support
- Proper handling of:
  - Combining characters
  - Surrogate pairs (UTF-16)
  - Grapheme clusters
  - Normalization forms
- Case operations are Unicode-aware

### Format System Features
- Type-safe compile-time checking
- Custom format specifiers:
  - `{}` - Default formatting
  - `{nh}` - Hex without prefix (no 0x)
  - Custom radix via `fg_FormatIntFormat<radix>`
- Three formatting approaches:
  - `CFormat` - Object-oriented, best for building complex strings
  - `_f` literal - Concise, best for inline formatting
  - `fg_Format` - Functional, best for simple format operations
- Automatic type deduction
- Efficient buffer management
- Supports all basic types and custom types with format traits

### Known Limitations
- Wildcard matching doesn't support full regex (use separate Regex module)
- ANSI conversion may lose data for Unicode strings
- Fixed strings have compile-time size limits
- Some algorithms not optimized for very long strings (>1MB)

### Best Practices
- Use `CStr` (UTF-8) as default string type
- Use `CStrSpan` for function parameters to avoid copies
- Prefer algorithms over manual iteration
- Use secure strings for sensitive data (passwords, keys)
- Reserve capacity when final size is known
- Use MultiReplace for batch replacements (more efficient)
- Consider Fixed strings for stack allocation in performance-critical code

### Common String Formatting Mistakes

**Compilation Error with `_f` Operator**

The `_f` string formatting operator requires the `NMib::NStr` namespace to be in scope:

```cpp
// INCORRECT - will cause compilation error
auto Result = "Value: {}"_f << 42;

// CORRECT - add using declaration before formatting
using namespace NMib::NStr;
auto Result = "Value: {}"_f << 42;
```

**Solution**: Add `using namespace NMib::NStr;` locally before using the `_f` formatting operator at the top of the function. If you are in a cpp file you can put the using declaration at the top of the file.
