#ifndef OF_PCH_H
#define OF_PCH_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include <optional>

#include <cstring>
#include <queue>
#include <sstream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>
#include <string>
#include <list>
#include <map>

#include <thread>
#include <mutex>

#ifdef ON1F_PLATFORM_WINDOWS
#include <windows.h>
#endif

#include <vulkan/vulkan.hpp>
#define GGLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#endif // OF_PCH_H