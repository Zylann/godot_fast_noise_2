#!/usr/bin/env python

import os
import sys

LIB_NAME = "libgdfastnoise2"
BIN_FOLDER = "project/addons/zylann.fastnoise2/bin"

# TODO Enhancement: not sure how to provide this as a SCons option since we get our environment *by running GodotCpp*...
#env_vars.Add(PathVariable("godot_cpp_path", "Path to the GodotCpp library source code", None, PathVariable.PathIsDir))
# TODO GDX: Have GodotCpp in thirdparty/ eventually
godot_cpp_path = os.environ.get("GODOT_CPP_PATH", "D:/PROJETS/INFO/GODOT/Engine/godot_cpp_fork")

# Dependency on GodotCpp.
# Use the same cross-platform configurations.
# TODO GDX: Make sure this isn't doing too much?
env = SConscript(godot_cpp_path + "/SConstruct")

# Dependency on FastNoise2
env.Append(CPPPATH = ["thirdparty/FastNoise/include"])
env.Append(LIBPATH = ["thirdparty/FastNoise/lib"])
env.Append(LIBS = ["FastNoise"])
# Fix problems loading the dynamic library since we put it next to our extension DLL, and not next to the executable
# (which would be very annoying in the editor, because we don't know where the editor will be and requiring the user to
# do fix it is not acceptable)
# env.Append(LINKFLAGS=["-Wl,-rpath," + os.path.abspath("includes/SumLib/lib/")])

# is_editor_build = (env["target"] == "editor")

sources = []
sources += [
    "src/register_types.cpp",
    "src/fast_noise_2.cpp"
]

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "{}/{}.{}.{}.framework/{}.{}.{}".format(
            BIN_FOLDER,
            LIB_NAME,
            env["platform"],
            env["target"],
            LIB_NAME,
            env["platform"],
            env["target"]
        ),
        source = sources
    )
else:
    library = env.SharedLibrary(
        "{}/{}{}{}".format(
            BIN_FOLDER,
            LIB_NAME,
            env["suffix"],
            env["SHLIBSUFFIX"]
        ),
        source = sources
    )

Default(library)
