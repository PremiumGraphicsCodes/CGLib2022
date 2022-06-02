#pragma once

#include <string>
#include <list>

namespace Crystal {
	namespace UI {

class IWindow
{
protected:
	explicit IWindow(const std::string& name) :
		name(name),
		_isVisible(true)
	{}

	virtual ~IWindow() {
		for (auto c : children) {
			delete c;
		}
	};

public:
	void add(IWindow* child) { children.push_back(child); }

	void clear() { children.clear(); }

	void show() { onShow(); }

	virtual void onShow() = 0;

	void open() { this->_isVisible = true; }

	void close() { this->_isVisible = false; }

	bool isVisible() const { return _isVisible; }

protected:
	std::string name;
	std::list<IWindow*> children;

private:
	bool _isVisible;

};
	}
}