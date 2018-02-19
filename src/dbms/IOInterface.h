#pragma once
#include <string>
class IOInterface {
public:

    IOInterface() {
        filename_ = "Default.txt";
    }

    IOInterface(const std::string& filename) {
        filename_ = filename;
    }

	virtual ~IOInterface() {

	}

    std::string getFilename() const {
        return filename_;
    }
    virtual void read() = 0;
    virtual void write() = 0;
	virtual std::string toString() = 0;

private:
    std::string filename_;

};
