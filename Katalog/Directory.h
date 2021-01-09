#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <BaseNode.h>
#include <string>

using std::string;

namespace Katalog {

	class Directory : public BaseNode {
	public:
		Directory(string nome, string path = "");
		long getSize() const;
		long getAllSize() const;
		string getIcon() const;

	private:

	};

}

#endif // DIRECTORY_H
