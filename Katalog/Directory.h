#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <BaseNode.h>
#include <string>

using std::string;

namespace Katalog {

	class Directory : public BaseNode {
	public:
		Directory(string nome, string path = "");
        virtual ~Directory() = default;
		Directory* clone() const override;
        long getSize() const override;
        long getAllSize() const override;
        string getInfo() const override;

	private:

	};

}

#endif // DIRECTORY_H
