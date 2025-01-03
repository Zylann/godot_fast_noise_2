FastNoise2 extension for Godot 4.4+
=======================================

WARNING: Work-in-progress.

This is a GDExtension bringing [FastNoise2](https://github.com/Auburn/FastNoise2) to Godot Engine. FastNoise2 provides SIMD-accelerated noise generation, which is significantly faster and more configurable than [FastNoiseLite](https://github.com/Auburn/FastNoiseLite).

Version of FastNoise2 used in this extension: `0.10.0-alpha`

This extension is ported from a former integration present in [godot_voxel](https://github.com/Zylann/godot_voxel).


How to install
----------------

Plugin packages are available in [Releases](https://github.com/Zylann/godot_fast_noise_2/releases).

Download one of the releases, and unpack it into your project. The archive contains an `addons` folder, to match the convention where plugins are stored in Godot projects. After unpacking, you should have the plugin under `addons/zylann.fastnoise2/`. You might have to restart the editor.

TODO Figure out what to do for Linux ARM64, the release of FastNoise2 only contains x86. 

TODO Figure out what to do for MacOS, we try to compile the extension as universal, but the release of FastNoise2 only has one .dylib for x86 (I am unable to test this, I have no Mac)


Usage
-------

A new class `FastNoise2` is available. It has similar settings to `FastNoiseLite` to get started quickly. The release package of `FastNoise2` also comes with a [graph tool](https://github.com/Auburn/FastNoise2/releases) to combine more complex noises together. Such graphs can be imported using the `encoded_node_tree` property. Note: make sure to use the graph tool from the same version of FastNoise2 that this extension supports.

Note: unlike `FastNoiseLite`, you need to manually update the noise after changing properties. This is because changing properties requires to update internal state, it is a bit more expensive and updating on every change would cause a lot of overhead when loading the resource. Thread-safety could be affected too if noise is generating in a thread while settings are changed. TODO Find a workaround to improve UX.

### GDScript

TODO GDScript code


### C#

You can use this class using "variant calls" (using `call` with strings for function names).
Alternatively, you could try using a [C# binding](https://github.com/Auburn/FastNoise2Bindings) directly.

TODO Low-level dynamic C interface with C# binding


### Native languages

You can use this class from a C++ module, or another GDExtension, using "variant calls" (using `call` with strings for function names).
Alternatively, you could try depending on the library directly.

TODO Low-level dynamic C interface


How to build
-------------

- Download FastNoise2's release and unpack its contents under a `thirdparty/` folder
- Download GodotCpp, unpack its contents somewhere and specify its path as an environment variable (see `SConscript`) (TODO improve this)
- Copy FastNoise2 shared library (.so, .dll etc) to `project/addons/zylann.fastnoise2/bin`
- Run SCons. See GDExtension documentation about possible parameters.
