def apply(config, args):
    config["baseimg"] = "private/civ5/libCvGameCoreDLL.so"
    config["myimg"] = "private/beyond-earth/libCvGameCoreDLL_Expansion1.so"
    # config["mapfile"] = "private/civ5/libCvGameCoreDLL.map"
    config["source_directories"] = ["src"]
    # config["show_line_numbers_default"] = True
    config["arch"] = "x86"
    # config["map_format"] = "gnu" # gnu, mw, ms
    # config["build_dir"] = "build/" # only needed for mw and ms map format
    # config["expected_dir"] = "expected/" # needed for -o
    # config["makeflags"] = []
    config["objdump_executable"] = "objdump"
    # Doesn't work
    # config["objdump_flags"] = ["-d", "--demangle"]
    # Force x86
    config["objdump_flags"] = ["-m", "i386"]
