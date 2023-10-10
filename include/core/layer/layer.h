#ifndef LAYER_H
#define LAYER_H

#include <of_pch.h>

namespace O1F4Engine
{
	class Layer {
	public:
		Layer() = default;
		Layer(const std::string& name) : name {name} {}

		Layer(const Layer&) = default;
		Layer(Layer&&) = default;
		Layer& operator = (const Layer&) = default;
		Layer& operator = (Layer&&) = default;
		virtual ~Layer() = default;

		virtual void init();
		virtual void update();
		virtual void render();
		virtual void shutdown();
	private:
		std::string name;
	};
}

#endif // I_LAYER_H