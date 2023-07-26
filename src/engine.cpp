#include <engine.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <service_locator.h>

#include "platform/glfw_window.h"

void On1FourEngine::Init()
{
  std::cout << "Initialize window" << std::endl;

  ServiceLocator::Provide(new CustomWindow());
}