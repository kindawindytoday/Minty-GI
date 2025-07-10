# What?
This is the source code of the Minty-GI!
We decided to leak it cause of Minty-GI getting discontinued, due to various AC updates.

# How to use it?
It's NOT compilable out-of-box. Lot of things (bypasses, encryption, few functions, all the offsets) were removed.
This source code is not meant for people to just rename the project and sell as their own.
Think of it as a manual, something that can help you learning to make your own projects.

# How to use the code base properly?
We've tried to make the code base as user-friendly as possible.
It's object-oriented, written in modern C++, without many dependencies.
Here's how you can use it:

\- **Bootstrap**\
--| dllmain.cpp // entry point of the application, starting all the required threads\
--| threads.cpp // define main threads here
  
\- **Bypass**\
--| bypass.cpp // Maybe something was here..
  
\- **Config**\
--| ConfigManager.cpp // Here is the config manager. It saves\loads all the settings to\from chosen config file. Many config files can be created
  
\- **Engine**\
--| SDK.cpp // Here starts the interesting part. You can define here any complex engine functions, e.g. "Entity::GetName()"\
--| SDK_offsets.h // Define all the functors with their offsets here. In this code, every offset is replaced with 0x0, which was stated above.\
--| SDK_types.h // Define some game structs or enums here\
--| SDK_utils.h // Defines all the classes and macro required for the SDK
  
\- **Frameworks**\
--| ... // Contains project dependencies, like Dear ImGui
  
\- **Functions**\
--| ... // Contains all the functions, separated into categories\
--| Feature.h // "Feature" class\
--| FeatureManager.h // Code for managing modules and their features
  
\- **GUI**\
--| DirectX\
----| DirectXHook.cpp // Code to initialize DX11 hook\
--| Menu\
----| Hotkey.cpp // "Hotkey" class\
----| InitGUI.cpp // Some menu initialization code - fonts, images, themes, ...\
----| MainGUI.cpp // Menu layout code
  
\- **Resources**\
--| ... // Put all the images and fonts here
  
\- **Utils**\
--| ... // Some miscellaneous stuff

# "Feature" class
It holds all the info about every single feature.
```
std::string m_Name;                // Function name, appears in menu and config files
std::string m_Description;         // Function description, appears in menu

Hotkey h_Enable;                   // Hotkey that toggles the function

ConfigField<bool> m_Enabled;       // Config field, thats holds "enabled" var of the function

virtual void Options()        {};  // ImGui code that is used in function settings
virtual void Status()         {};  // Mostly unused. Put some text here, to display in "Active functions" window
virtual void OnUpdate()       {};  // Code that gets called every frame
virtual void ProcessHotkeys() {};  // Stuff like "if (hotkey.IsPressed) {...}". Also gets called every frame, but separated to make code cleaner

virtual void InitConfig()     {};  // Gets called when program starts, and when you load a config. Init some function variables here
virtual void InitHooks()      {};  // Gets called when program starts. Init your hooks here

Feature(const char* name, const char* description); // Just a ctor, that inits variables.
```
