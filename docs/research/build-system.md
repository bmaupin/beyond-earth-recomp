# Research

## Beyond Earth game core

#### Metadata

- Last modification date: [2015-12-21](https://steamdb.info/depot/328351/manifests/)

#### Binary details

```
$ file libCvGameCoreDLL_Expansion1.so
libCvGameCoreDLL_Expansion1.so: ELF 32-bit LSB shared object, Intel 80386, version 1 (SYSV), dynamically linked, BuildID[sha1]=2db313915140d768a9461aff08a9d8e692be407f, with debug_info, not stripped
```

```
$ readelf -h libCvGameCoreDLL_Expansion1.so
ELF Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              DYN (Shared object file)
  Machine:                           Intel 80386
  Version:                           0x1
  Entry point address:               0x2b0b60
  Start of program headers:          52 (bytes into file)
  Start of section headers:          120269312 (bytes into file)
  Flags:                             0x0
  Size of this header:               52 (bytes)
  Size of program headers:           32 (bytes)
  Number of program headers:         7
  Size of section headers:           40 (bytes)
  Number of section headers:         39
  Section header string table index: 36
```

```
$ readelf -p .comment libCvGameCoreDLL_Expansion1.so

String dump of section '.comment':
  [     0]  GCC: (crosstool-NG 1.17.0) 4.6.3
  [    21]  clang version 3.4.1 (tags/RELEASE_34/dot1-rc2)
```

```
$ readelf -A libCvGameCoreDLL_Expansion1.so
```

```
$ readelf -S libCvGameCoreDLL_Expansion1.so | grep -E 'debug|symtab|strtab'
  [27] .debug_aranges    PROGBITS        00000000 9807e4 013e80 00      0   0  1
  [28] .debug_pubnames   PROGBITS        00000000 994664 d39937 00      0   0  1
  [29] .debug_info       PROGBITS        00000000 16cdf9b 397820f 00      0   0  1
  [30] .debug_abbrev     PROGBITS        00000000 50461aa 068e86 00      0   0  1
  [31] .debug_line       PROGBITS        00000000 50af030 26c3c5 00      0   0  1
  [32] .debug_str        PROGBITS        00000000 531b3f5 123586b 01  MS  0   0  1
  [33] .debug_loc        PROGBITS        00000000 6550c60 5eb999 00      0   0  1
  [34] .debug_pubtypes   PROGBITS        00000000 6b3c5f9 60e69b 00      0   0  1
  [35] .debug_ranges     PROGBITS        00000000 714ac94 167bf0 00      0   0  1
  [36] .shstrtab         STRTAB          00000000 72b2884 00017a 00      0   0  1
  [37] .symtab           SYMTAB          00000000 72b3018 0846e0 10     38 6531  4
  [38] .strtab           STRTAB          00000000 73376f8 1c03ea 00      0   0  1
```

```
$ readelf -SW libCvGameCoreDLL_Expansion1.so | grep debug
  [27] .debug_aranges    PROGBITS        00000000 9807e4 013e80 00      0   0  1
  [28] .debug_pubnames   PROGBITS        00000000 994664 d39937 00      0   0  1
  [29] .debug_info       PROGBITS        00000000 16cdf9b 397820f 00      0   0  1
  [30] .debug_abbrev     PROGBITS        00000000 50461aa 068e86 00      0   0  1
  [31] .debug_line       PROGBITS        00000000 50af030 26c3c5 00      0   0  1
  [32] .debug_str        PROGBITS        00000000 531b3f5 123586b 01  MS  0   0  1
  [33] .debug_loc        PROGBITS        00000000 6550c60 5eb999 00      0   0  1
  [34] .debug_pubtypes   PROGBITS        00000000 6b3c5f9 60e69b 00      0   0  1
  [35] .debug_ranges     PROGBITS        00000000 714ac94 167bf0 00      0   0  1
```

```
$ readelf --debug-dump=info libCvGameCoreDLL_Expansion1.so | head -100
Contents of the .debug_info section:

  Compilation Unit @ offset 0:
   Length:        0x393c0 (32-bit)
   Version:       4
   Abbrev Offset: 0
   Pointer Size:  4
 <0><b>: Abbrev Number: 1 (DW_TAG_compile_unit)
    <c>   DW_AT_producer    : (indirect string, offset: 0): clang version 3.4.1 (tags/RELEASE_34/dot1-rc2)
    <10>   DW_AT_language    : 4        (C++)
    <12>   DW_AT_name        : (indirect string, offset: 0x2f): ../../../Civ5/src/App/CvGameCoreDLL_Expansion1/CvAIFactClasses.cpp
    <16>   DW_AT_low_pc      : 0
    <1a>   DW_AT_stmt_list   : 0
    <1e>   DW_AT_comp_dir    : (indirect string, offset: 0x72): /var/jenkins/workspace/CivBE__Linux/Branches/CivBE/Port/Aspyr/Public/Mac
    <22>   DW_AT_APPLE_optimized: 1
 <1><22>: Abbrev Number: 2 (DW_TAG_namespace)
    <23>   DW_AT_name        : (indirect string, offset: 0xc2d35b): Hex
    <27>   DW_AT_decl_file   : 2
    <28>   DW_AT_decl_line   : 43
 <2><29>: Abbrev Number: 3 (DW_TAG_variable)
    <2a>   DW_AT_name        : (indirect string, offset: 0xbb): g_UnitHex
    <2e>   DW_AT_type        : <0x36>
    <32>   DW_AT_decl_file   : 2
    <33>   DW_AT_decl_line   : 349
 <2><35>: Abbrev Number: 0
 <1><36>: Abbrev Number: 4 (DW_TAG_array_type)
    <37>   DW_AT_type        : <0x42>
 <2><3b>: Abbrev Number: 5 (DW_TAG_subrange_type)
    <3c>   DW_AT_type        : <0x3d6>
    <40>   DW_AT_upper_bound : 5
 <2><41>: Abbrev Number: 0
 <1><42>: Abbrev Number: 6 (DW_TAG_const_type)
    <43>   DW_AT_type        : <0x47>
 <1><47>: Abbrev Number: 7 (DW_TAG_structure_type)
    <48>   DW_AT_name        : (indirect string, offset: 0xfdc): HEXVec
    <4c>   DW_AT_byte_size   : 16
    <4d>   DW_AT_decl_file   : 2
    <4e>   DW_AT_decl_line   : 116
 <2><4f>: Abbrev Number: 8 (DW_TAG_member)
    <50>   DW_AT_type        : <0x58>
    <54>   DW_AT_decl_file   : 2
    <55>   DW_AT_decl_line   : 183
    <56>   DW_AT_data_member_location: 0
    <57>   DW_AT_accessibility: 1       (public)
 <2><58>: Abbrev Number: 9 (DW_TAG_union_type)
    <59>   DW_AT_byte_size   : 16
    <5a>   DW_AT_decl_file   : 2
    <5b>   DW_AT_decl_line   : 183
 <3><5c>: Abbrev Number: 8 (DW_TAG_member)
    <5d>   DW_AT_type        : <0x65>
    <61>   DW_AT_decl_file   : 2
    <62>   DW_AT_decl_line   : 184
    <63>   DW_AT_data_member_location: 0
    <64>   DW_AT_accessibility: 1       (public)
 <3><65>: Abbrev Number: 10 (DW_TAG_structure_type)
    <66>   DW_AT_byte_size   : 12
    <67>   DW_AT_decl_file   : 2
    <68>   DW_AT_decl_line   : 184
 <4><69>: Abbrev Number: 11 (DW_TAG_member)
    <6a>   DW_AT_name        : (indirect string, offset: 0x993942): x
    <6e>   DW_AT_type        : <0x3c3>
    <72>   DW_AT_decl_file   : 2
    <73>   DW_AT_decl_line   : 184
    <74>   DW_AT_data_member_location: 0
    <75>   DW_AT_accessibility: 1       (public)
 <4><76>: Abbrev Number: 11 (DW_TAG_member)
    <77>   DW_AT_name        : (indirect string, offset: 0x1c02b9): y
    <7b>   DW_AT_type        : <0x3c3>
    <7f>   DW_AT_decl_file   : 2
    <80>   DW_AT_decl_line   : 184
    <81>   DW_AT_data_member_location: 4
    <82>   DW_AT_accessibility: 1       (public)
 <4><83>: Abbrev Number: 11 (DW_TAG_member)
    <84>   DW_AT_name        : (indirect string, offset: 0x33994c): z
    <88>   DW_AT_type        : <0x3c3>
    <8c>   DW_AT_decl_file   : 2
    <8d>   DW_AT_decl_line   : 184
    <8e>   DW_AT_data_member_location: 8
    <8f>   DW_AT_accessibility: 1       (public)
 <4><90>: Abbrev Number: 0
 <3><91>: Abbrev Number: 11 (DW_TAG_member)
    <92>   DW_AT_name        : (indirect string, offset: 0xc02796): v
    <96>   DW_AT_type        : <0x3ca>
    <9a>   DW_AT_decl_file   : 2
    <9b>   DW_AT_decl_line   : 185
    <9c>   DW_AT_data_member_location: 0
    <9d>   DW_AT_accessibility: 1       (public)
 <3><9e>: Abbrev Number: 0
 <2><9f>: Abbrev Number: 12 (DW_TAG_member)
    <a0>   DW_AT_name        : (indirect string, offset: 0xc5): TRANSLATIONS
    <a4>   DW_AT_type        : <0x36>
    <a8>   DW_AT_decl_file   : 2
    <a9>   DW_AT_decl_line   : 277
    <ab>   DW_AT_external    : 1
    <ab>   DW_AT_declaration : 1
    <ab>   DW_AT_accessibility: 1       (public)
 <2><ac>: Abbrev Number: 12 (DW_TAG_member)
    <ad>   DW_AT_name        : (indirect string, offset: 0xd2): TRANSLATIONS_CLOCKWISE
    <b1>   DW_AT_type        : <0x36>
    <b5>   DW_AT_decl_file   : 2
```

## Civ 5 game core

#### Build system

#### Metadata

- Last modification date: [2015-06-11](https://steamdb.info/depot/282301/manifests/)

#### Binary details

```
$ file libCvGameCoreDLL_Expansion2.so
libCvGameCoreDLL_Expansion2.so: ELF 32-bit LSB shared object, Intel 80386, version 1 (SYSV), dynamically linked, BuildID[sha1]=52575e89433d2cec0d0ccdcc7c9d5baafa108d1b, stripped
```

```
$ readelf -h libCvGameCoreDLL_Expansion2.so
ELF Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              DYN (Shared object file)
  Machine:                           Intel 80386
  Version:                           0x1
  Entry point address:               0x127e0
  Start of program headers:          52 (bytes into file)
  Start of section headers:          5659608 (bytes into file)
  Flags:                             0x0
  Size of this header:               52 (bytes)
  Size of program headers:           32 (bytes)
  Number of program headers:         7
  Size of section headers:           40 (bytes)
  Number of section headers:         30
  Section header string table index: 29
```

```
$ readelf -p .comment libCvGameCoreDLL_Expansion2.so

String dump of section '.comment':
  [     0]  GCC: (crosstool-NG 1.17.0) 4.6.3
  [    21]  clang version 3.4.1 (tags/RELEASE_34/dot1-rc2)
```

```
$ readelf -A libCvGameCoreDLL_Expansion2.so
```

```
$ readelf -S libCvGameCoreDLL_Expansion2.so
There are 30 section headers, starting at offset 0x565bd8:

Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .note.gnu.bu[...] NOTE            00000114 000114 000024 00   A  0   0  4
  [ 2] .gnu.hash         GNU_HASH        00000138 000138 000024 04   A  3   0  4
  [ 3] .dynsym           DYNSYM          0000015c 00015c 001bb0 10   A  4   1  4
  [ 4] .dynstr           STRTAB          00001d0c 001d0c 0034d5 00   A  0   0  1
  [ 5] .gnu.version      VERSYM          000051e2 0051e2 000376 02   A  3   0  2
  [ 6] .gnu.version_d    VERDEF          00005558 005558 000038 00   A  4   2  4
  [ 7] .rel.dyn          REL             00005590 005590 00ab50 08   A  3   0  4
  [ 8] .rel.plt          REL             000100e0 0100e0 000ce8 08   A  3  10  4
  [ 9] .init             PROGBITS        00010dc8 010dc8 00002e 00  AX  0   0  4
  [10] .plt              PROGBITS        00010e00 010e00 0019e0 04  AX  0   0 16
  [11] .text             PROGBITS        000127e0 0127e0 444ddc 00  AX  0   0 16
  [12] .fini             PROGBITS        004575bc 4575bc 00001a 00  AX  0   0  4
  [13] .rodata           PROGBITS        004575e0 4575e0 051a95 00   A  0   0 16
  [14] .eh_frame_hdr     PROGBITS        004a9078 4a9078 01620c 00   A  0   0  4
  [15] .eh_frame         PROGBITS        004bf284 4bf284 062ee8 00   A  0   0  4
  [16] .gcc_except_table PROGBITS        0052216c 52216c 03ca10 00   A  0   0  4
  [17] .init_array       INIT_ARRAY      0055fc38 55ec38 000288 00  WA  0   0  4
  [18] .fini_array       FINI_ARRAY      0055fec0 55eec0 000004 00  WA  0   0  4
  [19] .ctors            PROGBITS        0055fec4 55eec4 000008 00  WA  0   0  4
  [20] .dtors            PROGBITS        0055fecc 55eecc 000008 00  WA  0   0  4
  [21] .jcr              PROGBITS        0055fed4 55eed4 000004 00  WA  0   0  4
  [22] .data.rel.ro      PROGBITS        0055fee0 55eee0 005fa0 00  WA  0   0 16
  [23] .dynamic          DYNAMIC         00565e80 564e80 0000e8 08  WA  4   0  4
  [24] .got              PROGBITS        00565f68 564f68 00008c 04  WA  0   0  4
  [25] .got.plt          PROGBITS        00566000 565000 000680 04  WA  0   0  4
  [26] .data             PROGBITS        00566680 565680 0003f8 00  WA  0   0  4
  [27] .bss              NOBITS          00566a78 565a78 21afd4 00  WA  0   0  8
  [28] .comment          PROGBITS        00000000 565a78 000050 01  MS  0   0  1
  [29] .shstrtab         STRTAB          00000000 565ac8 00010d 00      0   0  1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  D (mbind), p (processor specific)
```

```
$ readelf -S libCvGameCoreDLL_Expansion2.so | grep -E 'debug|symtab|strtab'
  [29] .shstrtab         STRTAB          00000000 565ac8 00010d 00      0   0  1
```

```
$ readelf -SW libCvGameCoreDLL_Expansion2.so | grep debug
```

```
$ readelf --debug-dump=info libCvGameCoreDLL_Expansion2.so | head -100
```
