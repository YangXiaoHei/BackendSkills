General options:

-aarch64-neon-syntax                 - Choose style of NEON code to emit from AArch64 backend:
=generic                           -   Emit generic NEON assembly
=apple                             -   Emit Apple-style NEON assembly
-arch=<string>                       - architecture(s) from a Mach-O file to dump
-arch-name=<string>                  - Target arch to disassemble for, see -version for available targets
-archive-headers                     - Print archive headers for Mach-O archives (requires -macho)
-archive-member-offsets              - Print the offset to each archive member for Mach-O archives (requires -macho and -archive-headers)
-bind                                - Display mach-o binding info
-color                               - use colored syntax highlighting (default=autodetect)
-data-in-code                        - Print the data in code table for Mach-O objects (requires -macho)
-dis-symname=<string>                - disassemble just this symbol's instructions (requires -macho)
-disassemble                         - Display assembler mnemonics for the machine instructions
-disassemble-all                     - Display assembler mnemonics for the machine instructions
-dsym=<string>                       - Use .dSYM file for debug info
-dwarf                               - Dump of dwarf debug sections:
=frames                            -   .debug_frame
-dylib-id                            - Print the shared library's id for the dylib Mach-O file (requires -macho)
-dylibs-used                         - Print the shared libraries used for linked Mach-O files (requires -macho)
-exports-trie                        - Display mach-o exported symbols
-fault-map-section                   - Display contents of faultmap section
-filter-print-funcs=<function names> - Only print IR for functions whose name match this for all print-[before|after][-all] options
-full-leading-addr                   - Print full leading address
-g                                   - Print line information from debug info if available
-indirect-symbols                    - Print indirect symbol table for Mach-O objects (requires -macho)
-info-plist                          - Print the info plist section as strings for Mach-O objects (requires -macho)
-lazy-bind                           - Display mach-o lazy binding info
-line-numbers                        - Display source line numbers with disassembly. Implies disassemble object
-link-opt-hints                      - Print the linker optimization hints for Mach-O objects (requires -macho)
-macho                               - Use MachO specific object file parser
-mattr=<a1,+a2,-a3,...>              - Target specific attributes
-mcpu=<cpu-name>                     - Target a specific cpu type (-mcpu=help for details)
-no-leading-addr                     - Print no leading address
-no-leading-headers                  - Print no leading headers
-no-show-raw-insn                    - When disassembling instructions, do not print the instruction bytes.
-no-symbolic-operands                - do not symbolic operands when disassembling (requires -macho)
-non-verbose                         - Print the info for Mach-O objects in non-verbose or numeric form (requires -macho)
-objc-meta-data                      - Print the Objective-C runtime meta data for Mach-O files (requires -macho)
-print-after-all                     - Print IR after each pass
-print-before-all                    - Print IR before each pass
-print-imm-hex                       - Use hex format for immediate values
-private-header                      - Display only the first format specific file header
-private-headers                     - Display format specific file headers
-r                                   - Display the relocation entries in the file
-raw-clang-ast                       - Dump the raw binary contents of the clang AST section
-rebase                              - Display mach-o rebasing info
-rng-seed=<seed>                     - Seed for the random number generator
-s                                   - Display the content of each section
-section=<string>                    - Operate on the specified sections only. With -macho dump segment,section
-section-headers                     - Display summaries of the headers for each section.
-source                              - Display source inlined with disassembly. Implies disassmble object
-start-address=<address>             - Disassemble beginning at address
-stop-address=<address>              - Stop disassembly at address
-t                                   - Display the symbol table
-time-passes                         - Time each pass, printing elapsed time for each on exit
-triple=<string>                     - Target triple to disassemble for, see -version for available targets
-universal-headers                   - Print Mach-O universal headers (requires -macho)
-unwind-info                         - Display unwind information
-verify-debug-info                   -
-verify-dom-info                     - Verify dominator info (time consuming)
-weak-bind                           - Display mach-o weak binding info
-x86-asm-syntax                      - Choose style of code to emit from X86 backend:
=att                               -   Emit AT&T-style assembly
=intel                             -   Emit Intel-style assembly

