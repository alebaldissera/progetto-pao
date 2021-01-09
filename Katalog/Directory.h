#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <BaseNode.h>
#include <string>

using std::string;

namespace Katalog {

	class Directory : public BaseNode {
	public:
		Directory(string nome, string path = "");
        long getSize() override;
        long getAllSize() override;
        string getIcon() const override;

	private:

	};

}

#endif // DIRECTORY_H
